// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_GameInstance.h"
#include "CY_Define.h"
#include "CY_SingletonManager.h"
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

	CreateGameCore();
	CreateManagers();

	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UCY_GameInstance::Tick));
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

void UCY_GameInstance::CreateGameCore()
{
	// custom kernel
}

void UCY_GameInstance::CreateManagers()
{
	if (TObjectPtr<UCY_SingletonManager> SingletonManager = UCY_SingletonManager::CreateInstance())
	{
		SingletonManager->BuiltInInitializeSingletons();
	}
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
}

void UCY_GameInstance::RegistState()
{
	if (UCY_SceneManager::HasInstance == nullptr)
	{
		CY_CHECK(false);
		return;
	}

	//gSceneMng.RegisterSceneState(static_cast<uint8>(EGameSceneType::Title), TEXT("Title"), UCY_SceneTitle::StaticClass());
}

void UCY_GameInstance::LoadBaseWorld()
{

}
