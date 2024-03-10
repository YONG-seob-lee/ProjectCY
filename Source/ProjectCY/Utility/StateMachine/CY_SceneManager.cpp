// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SceneManager.h"
#include "CY_StateMachine.h"
#include "CY_Define.h"

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
}

void UCY_SceneManager::RegisterSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType) const
{
	SceneStateMachine->RegistState(SceneId, Name, SceneType);
}
