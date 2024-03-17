// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SceneManager.h"

#include "CY_BasicGameUtility.h"
#include "CY_CameraManager.h"
#include "CY_StateMachine.h"
#include "CY_Define.h"
#include "CY_FadeSceneTool.h"
#include "CY_GameInstance.h"
#include "CY_InputManager.h"
#include "CY_LevelLogicBase.h"
#include "CY_SceneBT.h"
#include "CY_Utility.h"
#include "CY_WidgetManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

UCY_SceneManager::UCY_SceneManager()
{
	
}

UCY_SceneManager::~UCY_SceneManager()
{
}

void UCY_SceneManager::Initialize()
{
	SceneStateMachine = CY_NewObject<UCY_StateMachine>(this, UCY_SceneManager::StaticClass());
	SceneStateMachine->AddToRoot();
	SceneStateMachine->Create();

	FadeTool = MakeWeakObjectPtr(CY_NewObject<UCY_FadeSceneTool>());
	
	if(!FadeTool.IsValid())
	{
		return;
	}
}

void UCY_SceneManager::Finalize()
{
}

void UCY_SceneManager::Tick(float DeltaTime)
{
	if (SceneStateMachine)
	{
		SceneStateMachine->Tick(DeltaTime);
	}

	if(FadeTool.IsValid())
	{
		FadeTool->Tick(DeltaTime);
	}
}

void UCY_SceneManager::RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType) const
{
	SceneStateMachine->RegistState(SceneId, Name, SceneType);
}

bool UCY_SceneManager::LoadLevelByPath(FCY_LoadLevelInitialized Delegate, const FName& PackagePath /* = FName() */, bool bAbsolute /* = true */)
{
	if(gInstance.HasInstance() == false)
	{
		return false;
	}

	TObjectPtr<UWorld> World = gInstance.GetWorld();
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

void UCY_SceneManager::LoadLevelBySoftObjectPtr(TSoftObjectPtr<UWorld> LevelObjectPtr, FCY_LoadLevelInitialized Delegate)
{
	
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

	if(gInstancePtr == nullptr)
	{
		return;
	}

	for (TActorIterator<ACY_LevelLogicBase> it(gInstance.GetWorld()); it; ++it)
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
		SceneLogic = Cast<ACY_LevelLogicBase>(gInstance.GetWorld());
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