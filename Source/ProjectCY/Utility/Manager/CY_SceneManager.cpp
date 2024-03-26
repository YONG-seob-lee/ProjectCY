// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SceneManager.h"

#include "CY_BasicGameUtility.h"
#include "CY_CameraManager.h"
#include "CY_StateMachine.h"
#include "CY_Define.h"
#include "CY_FadeSceneTool.h"
#include "CY_InputManager.h"
#include "CY_LevelLogicBase.h"
#include "CY_SceneBT.h"
#include "CY_SceneTitle.h"
#include "CY_Scene_PalWorld.h"
#include "CY_Utility.h"
#include "CY_WidgetManager.h"
#include "EngineUtils.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"

UCY_SceneManager::UCY_SceneManager()
{
	
}

UCY_SceneManager::~UCY_SceneManager()
{
}

void UCY_SceneManager::BuiltInInitialize()
{
	SceneStateMachine = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	SceneStateMachine->AddToRoot();
	SceneStateMachine->Create();
}

void UCY_SceneManager::Initialize()
{
	FadeTool = MakeWeakObjectPtr(CY_NewObject<UCY_FadeSceneTool>());
	
	if(!FadeTool.IsValid())
	{
		return;
	}
}

void UCY_SceneManager::Finalize()
{
	FadeTool = nullptr;
	LoadLevelInitialized.Unbind();
	LoadLevelInitialized = nullptr;
	UnregisterSceneBehaviorTree();
}

void UCY_SceneManager::BuiltInFinalize()
{
	SceneStateMachine->Destroy();
	SceneStateMachine->RemoveFromRoot();
	SceneStateMachine = nullptr;
}

void UCY_SceneManager::Tick(float DeltaTime)
{
	if(ChangeSceneData.Step == ECY_ChangeSceneStep::Complete)
	{
		if (SceneStateMachine)
		{
			SceneStateMachine->Tick(DeltaTime);
		}	
	}
	else if(ChangeSceneData.Step == ECY_ChangeSceneStep::PrepareSceneState)
	{
		const TObjectPtr<UCY_SceneBase> CurrentScene = GetCurrentScene();
		CurrentScene->TickLoading(DeltaTime);

		if(CurrentScene->IsCompleteLoading())
		{
			ChangeSceneData.Step = ECY_ChangeSceneStep::Complete;
		}
	}
	

	if(FadeTool.IsValid())
	{
		FadeTool->Tick(DeltaTime);
	}
}

TObjectPtr<UCY_SceneBase> UCY_SceneManager::GetCurrentScene()
{
	if(SceneStateMachine)
	{
		Cast<UCY_SceneBase>(SceneStateMachine->GetCurrentState());
	}

	return nullptr;
}

void UCY_SceneManager::RegisterScenes() const
{
	RegistSceneState(static_cast<uint8>(ECY_GameSceneType::Title), TEXT("Title"), UCY_SceneTitle::StaticClass());
	RegistSceneState(static_cast<uint8>(ECY_GameSceneType::PalWorld), TEXT("PalWorld"), UCY_Scene_PalWorld::StaticClass());
}

void UCY_SceneManager::SceneLoadComplete(float LoadTime, const FString& LevelName)
{
	gInputMng.CreateInputPawn();
	ActiveLevels.Empty();

	const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld();
	const TArray<ULevelStreaming*>& Levels = World->GetStreamingLevels();

	for(int32 i = 0 ; i < Levels.Num() ; i++)
	{
		if(World->GetCurrentLevel()->GetName().Equals(Levels[i]->PackageNameToLoad.ToString(), ESearchCase::IgnoreCase))
		{
			ActiveLevels.Emplace(Levels[i]->PackageNameToLoad.ToString(), true);
		}
		else
		{
			ActiveLevels.Emplace(Levels[i]->PackageNameToLoad.ToString(), false);
		}
	}

	ExecuteLoadLevelDelegate(LevelName);
}

void UCY_SceneManager::ExecuteLoadLevelDelegate(const FString& LevelName /* = TEXT("") */)
{
	if(LoadLevelInitialized.IsBound())
	{
		const FCY_LoadLevelInitialized Delegate = LoadLevelInitialized;
		LoadLevelInitialized.Unbind();
		
		Delegate.Execute(LevelName.IsEmpty() ? UCY_BasicGameUtility::GetGameWorld()->GetMapName() : LevelName);
	}
}

bool UCY_SceneManager::LoadLevelByPath(FCY_LoadLevelInitialized Delegate, const FName& PackagePath /* = FName() */, bool bAbsolute /* = true */)
{
	if(UCY_BasicGameUtility::HasGameInstance() == false)
	{
		return false;
	}

	TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld();
	if(World == nullptr)
	{
		return false;
	}

	gInputMng.DestroyInputPawn();
	gCameraMng.DestroyAllCameras();

	UGameplayStatics::OpenLevel(World, PackagePath, bAbsolute);

	LoadLevelInitialized.Unbind();
	LoadLevelInitialized = Delegate;

	return true;
}

bool UCY_SceneManager::LoadLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld>& LevelObjectPtr, const FCY_LoadLevelInitialized& Delegate)
{
	const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld();
	if(IsValid(World) == false)
	{
		return false;
	}

	gInputMng.DestroyInputPawn();
	gCameraMng.DestroyAllCameras();

	bool bSuccess = true;
	ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(World, LevelObjectPtr, FVector::ZeroVector, FRotator::ZeroRotator, bSuccess);

	if(bSuccess)
	{
		LoadLevelInitialized.Unbind();
		LoadLevelInitialized = Delegate;
	}

	return true;
}

void UCY_SceneManager::ChangeScene(ECY_GameSceneType SceneType, const FName& LevelPackagePath /* = NAME_None */)
{
	CY_LOG(TEXT("UCY_SceneManager::ChangeScene - SceneId(%d), LevelPath(%s)"), SceneType, *LevelPackagePath.ToString());

	if(OnChangeScene.IsBound())
	{
		OnChangeScene.Broadcast(SceneType);
	}

	ChangeSceneData.Step = ECY_ChangeSceneStep::Ready;
	ChangeSceneData.SceneType = SceneType;
	ChangeSceneData.LevelPackagePath = LevelPackagePath;

	ChangeSceneStep_LoadLevel();

	gWidgetMng.ClearExclusiveLayer();
}

void UCY_SceneManager::SetSceneBehaviorTreeAsset(TObjectPtr<UBehaviorTree> BTAsset)
{
}

void UCY_SceneManager::RegistSceneBehaviorTree()
{
}


void UCY_SceneManager::RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType) const
{
	SceneStateMachine->RegistState(SceneId, Name, SceneType);
}

bool UCY_SceneManager::ChangeSceneStep_LoadLevel()
{
	if(ChangeSceneData.LevelPackagePath == NAME_None)
	{
		ChangeSceneStep_SetSceneState(static_cast<uint8>(ChangeSceneData.SceneType));
		return true;
	}

	ChangeSceneData.Step = ECY_ChangeSceneStep::LoadLevel;

	UnregisterSceneBehaviorTree();
	gCameraMng.ResetData();
	OnStartLevelLoading.Broadcast(ChangeSceneData.LevelPackagePath.ToString());

	return LoadLevelByPath(FCY_LoadLevelInitialized::CreateUObject(this, &UCY_SceneManager::OnCompleteLevelLoading), ChangeSceneData.LevelPackagePath, true);
}

void UCY_SceneManager::ChangeSceneStep_SetSceneState(uint8 SceneId)
{
	ChangeSceneData.Step = ECY_ChangeSceneStep::PrepareSceneState;

	//SceneStateMachine->GetState(SceneId);
	if(SceneStateMachine)
	{
		SceneStateMachine->SetState(SceneId);
	}
}

void UCY_SceneManager::OnCompleteLevelLoading(const FString& LevelPackagePath)
{
	RegisterSceneBehaviorTree();

	ChangeSceneStep_SetSceneState(static_cast<uint8>(ChangeSceneData.SceneType));

	OnFinishedLevelLoading.Broadcast(LevelPackagePath);
}

void UCY_SceneManager::RegisterSceneBehaviorTree()
{
	if(SceneLogic != nullptr)
	{
		return;
	}

	if(SceneBehaviorTree == nullptr)
	{
		return;
	}

	if(UCY_BasicGameUtility::HasGameInstance() == false)
	{
		return;
	}

	for (TActorIterator<ACY_LevelLogicBase> it(UCY_BasicGameUtility::GetGameWorld()); it; ++it)
	{
		if (it->GetName().Equals(TEXT("SceneLogicActor"), ESearchCase::IgnoreCase) == true) {
			SceneLogic = *it;
			break;
		}
	}

	if (SceneLogic != nullptr)
	{
		if (SceneLogic->SetBehaviorTreeAsset(SceneBehaviorTree))
			SceneLogic->StartBehaviorTree();
	}
	else
	{
		SceneLogic = Cast<ACY_LevelLogicBase>(UCY_BasicGameUtility::GetGameWorld());
		if (SceneLogic)
		{
			if (SceneLogic->SetBehaviorTreeAsset(SceneBehaviorTree))
				SceneLogic->StartBehaviorTree();
		}
	}
}

void UCY_SceneManager::UnregisterSceneBehaviorTree()
{
	if(SceneLogic != nullptr)
	{
		SceneLogic->RemoveBehaviorTree();
		SceneLogic = nullptr;
	}
	if(CustomSceneBT)
	{
		CustomSceneBT->StopBT();
		CustomSceneBT = nullptr;
	}
}
