// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_GameInstance.h"

#include "CY_BasicGameUtility.h"
#include "CY_Define.h"
#include "CY_SingletonManager.h"
#include "CY_SceneTitle.h"
#include "CY_SceneManager.h"


UCY_GameInstance::UCY_GameInstance()
{
	FWorldDelegates::OnStartGameInstance.AddUObject(this, &UCY_GameInstance::GameInstanceStart);
}

UCY_GameInstance::~UCY_GameInstance()
{
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
}

void UCY_GameInstance::Init()
{
	Super::Init();

	ProcessInitialize();

	if (static_cast<ECY_LaunchProcessType>(ProcessType) != ECY_LaunchProcessType::ProcessFinished)
	{
		CY_CHECK(false);
		RestartGame();
	}
}

void UCY_GameInstance::Shutdown()
{
	ProcessFinalize();
	if(ProcessType != ECY_LaunchProcessType::BasicUtility)
	{
		CY_CHECK(false);
		return;
	}
	ProcessType = ECY_LaunchProcessType::None;
	
	Super::Shutdown();
}

void UCY_GameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
}

void UCY_GameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);

	gSceneMng.SceneLoadComplete(LoadTime, MapName);
}

bool UCY_GameInstance::Tick(float DeltaSeconds)
{
	if(ProcessType == ECY_LaunchProcessType::End)
	{
		UCY_SingletonManager::GetInstance()->TickSingletons(DeltaSeconds);
	}

	if(ProcessType == ECY_LaunchProcessType::ProcessFinished)
	{
		gSceneMng.ExecuteLoadLevelDelegate();
		ProcessType = ECY_LaunchProcessType::End;
	}
	
	return true;
}

void UCY_GameInstance::ProcessInitialize()
{
	ProcessType = ECY_LaunchProcessType::CreateManager;

	if (CreateBasicUtility() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::BasicUtility;
	if (CreateManagers() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::RegistManager;

	if (RegisterTick() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::RegistTick;
	
	if (RegisterState() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::LoadBaseWorld;
	
	if (LoadBaseWorld() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::ProcessFinished;
}

void UCY_GameInstance::ProcessFinalize()
{
	if(ProcessType != ECY_LaunchProcessType::End)
	{
		return;
	}

	ProcessType = ECY_LaunchProcessType::ProcessFinished;
	
	if(UnLoadBaseWorld() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::LoadBaseWorld;

	if(UnRegisterTick() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::RegistTick;

	if(DestroyManagers() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::RegistManager;

	if(DestroyBasicUtility() == false)
	{
		return;
	}
	ProcessType = ECY_LaunchProcessType::BasicUtility;
}

bool UCY_GameInstance::CreateBasicUtility()
{
	if(UCY_BasicGameUtility::HasInstance() == false)
	{
		if(const TObjectPtr<UCY_BasicGameUtility> BasicGameUtility = UCY_BasicGameUtility::MakeInstance())
		{
			BasicGameUtility->Initialize(this);
			return true;
		}
	}
	return false;
}

bool UCY_GameInstance::CreateManagers()
{
	if (const TObjectPtr<UCY_SingletonManager> SingletonManager = UCY_SingletonManager::CreateInstance())
	{
		SingletonManager->BuiltInInitializeSingletons();
	}
	return true;
}

bool UCY_GameInstance::DestroyManagers()
{
	if (const TObjectPtr<UCY_SingletonManager> SingletonManager = UCY_SingletonManager::GetInstance())
	{
		SingletonManager->FinalizeSingletons();
	}

	UCY_SingletonManager::DestroyInstance();

	return true;
}

bool UCY_GameInstance::DestroyBasicUtility()
{
	if(const TObjectPtr<UCY_BasicGameUtility> BasicGameUtility = UCY_BasicGameUtility::GetInstance())
	{
		BasicGameUtility->Finalize();
		BasicGameUtility->RemoveInstance();
		return true;
	}
	return false;
}

void UCY_GameInstance::GameInstanceStart(UGameInstance* GameInstance)
{
	if (const TObjectPtr<UCY_SingletonManager> SingletonManager = UCY_SingletonManager::GetInstance())
	{
		SingletonManager->InitializeSingletons();
	}
}

bool UCY_GameInstance::RegisterTick()
{
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UCY_GameInstance::Tick));
	return true;
}

bool UCY_GameInstance::UnRegisterTick()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	return true;
}

bool UCY_GameInstance::RegisterState()
{
	if (UCY_SceneManager::HasInstance() == false)
	{
		CY_CHECK(false);
		return false;
	}

	gSceneMng.RegisterScenes();

	return true;
}

bool UCY_GameInstance::LoadBaseWorld()
{
	if(BaseWorld.IsValid())
	{
		gSceneMng.LoadLevelBySoftObjectPtr(BaseWorld, FCY_LoadLevelInitialized::CreateWeakLambda(this, [this](const FString& Value)
		{
			gSceneMng.ChangeScene(ECY_GameSceneType::Title);
			gSceneMng.SetSceneBehaviorTreeAsset(SceneBTAsset);
			gSceneMng.RegistSceneBehaviorTree();
		}));
		return true;
	}
	return false;
}

bool UCY_GameInstance::UnLoadBaseWorld()
{
	if(BaseWorld.IsValid())
	{
		BaseWorld = nullptr;
		return true;
	}

	return false;
}

void UCY_GameInstance::RestartGame()
{
	/*for (TActorIterator<ALevelSequenceActor> AIt(UCY_FunctionLibrary::GetGameWorld(), ALevelSequenceActor::StaticClass()); AIt; ++AIt)
	{
		ALevelSequenceActor* LevelSequenceActor = *AIt;
		if (LevelSequenceActor->GetSequence())
		{
			LevelSequenceActor->Destroy();
		}
	}*/
}
