// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_ContentsProcessManager.h"
#include "CY_StateMachine.h"
#include "CY_Define.h"

UCY_ContentsProcessManager::UCY_ContentsProcessManager()
{
}

UCY_ContentsProcessManager::~UCY_ContentsProcessManager()
{
}

void UCY_ContentsProcessManager::Initialize()
{
	StateMachine = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	StateMachine->AddToRoot();
	StateMachine->Create();
}

void UCY_ContentsProcessManager::Finalize()
{
	StateMachine->Destroy();
	StateMachine->RemoveFromRoot();
	StateMachine = nullptr;
}

void UCY_ContentsProcessManager::Tick(float DeltaTime)
{
	if (StateMachine)
	{
		StateMachine->Tick(DeltaTime);
	}
}
