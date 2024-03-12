// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_GameInstance.h"
#include "CY_Define.h"
#include "CY_SingletonManager.h"
#include "CY_SceneTitle.h"
#include "CY_SceneManager.h"


UCY_GameInstance::UCY_GameInstance()
{
}

UCY_GameInstance::~UCY_GameInstance()
{
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
}

void UCY_GameInstance::Init()
{
	Super::Init();

	uint8 ProcessType;
	ProcessInitialize(ProcessType);

	if (static_cast<ECY_LaunchProcessType>(ProcessType) != ECY_LaunchProcessType::ProcessFinished)
	{
		CY_CHECK(false);
		RestartGame();
	}
}

void UCY_GameInstance::Shutdown()
{
	DestroyManagers();
	DestroyGameCore();

	Super::Shutdown();
}

void UCY_GameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
}

void UCY_GameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);
}

bool UCY_GameInstance::Tick(float DeltaSeconds)
{
	UCY_SingletonManager::GetInstance()->TickSingletons(DeltaSeconds);

	return true;
}

void UCY_GameInstance::ProcessInitialize(uint8& CurrentProcessType)
{
	CurrentProcessType = static_cast<uint8>(ECY_LaunchProcessType::CreateManager);

	if (CreateManagers() == false)	return;
	CurrentProcessType = static_cast<uint8>(ECY_LaunchProcessType::RegistTick);

	if (RegistTick() == false)	return;
	CurrentProcessType = static_cast<uint8>(ECY_LaunchProcessType::RegistState);
	
	if (RegistState() == false) return;
	CurrentProcessType = static_cast<uint8>(ECY_LaunchProcessType::LoadBaseWorld);
	
	if (LoadBaseWorld() == false) return;
	CurrentProcessType = static_cast<uint8>(ECY_LaunchProcessType::ProcessFinished);
}

bool UCY_GameInstance::CreateManagers()
{
	if (TObjectPtr<UCY_SingletonManager> SingletonManager = UCY_SingletonManager::CreateInstance())
	{
		SingletonManager->BuiltInInitializeSingletons();
	}
	return true;
}

void UCY_GameInstance::DestroyManagers()
{
	if (TObjectPtr<UCY_SingletonManager> SingletonManager = UCY_SingletonManager::GetInstance())
	{
		SingletonManager->FinalizeSingletons();
	}

	UCY_SingletonManager::DestroyInstance();
}

void UCY_GameInstance::DestroyGameCore()
{
	if (TObjectPtr<UCY_SingletonManager> SingletonManager = UCY_SingletonManager::GetInstance())
	{
		SingletonManager->FinalizeSingletons();
	}

	UCY_SingletonManager::DestroyInstance();
}

bool UCY_GameInstance::RegistTick()
{
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UCY_GameInstance::Tick));
	return true;
}

bool UCY_GameInstance::RegistState()
{
	if (UCY_SceneManager::HasInstance == nullptr)
	{
		CY_CHECK(false);
		return false;
	}

	gSceneMng.RegisterSceneState(static_cast<uint8>(ECY_GameSceneType::Title), TEXT("Title"), UCY_SceneTitle::StaticClass());

	return true;
}

bool UCY_GameInstance::LoadBaseWorld()
{
	return true;
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
