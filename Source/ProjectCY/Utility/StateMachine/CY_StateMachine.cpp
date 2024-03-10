// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_StateMachine.h"
#include "CY_StateBase.h"
#include "CY_Define.h"

void UCY_StateMachine::Create()
{
}

void UCY_StateMachine::Destroy()
{
}

void UCY_StateMachine::Tick(float _fDeltaTime)
{
}

void UCY_StateMachine::RegistState(int8 Index, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType, UObject* Outer)
{
	if (EntireState.Find(Index) != nullptr)
	{
		CY_CHECK(false);
		return;
	}

	TObjectPtr<UObject> CustomOuter = Outer != nullptr ? Outer : this;
	TObjectPtr<UCY_StateBase> State = CY_NewObject<UCY_StateBase>(CustomOuter, SceneType);

	State->AddToRoot();
	State->Initialize(Index, Name);
	EntireState.Emplace(Index, State);
}

void UCY_StateMachine::UnregistStates()
{
	for (auto& State : EntireState)
	{
		if (State.Value != nullptr)
		{
			State.Value->Finalize();
			State.Value->RemoveFromRoot();
			State.Value = nullptr;
		}
	}

	EntireState.Empty();
}
