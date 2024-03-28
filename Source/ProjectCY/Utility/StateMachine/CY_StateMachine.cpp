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

void UCY_StateMachine::UnRegistStates()
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

TObjectPtr<UCY_StateBase> UCY_StateMachine::GetCurrentState()
{
	const TObjectPtr<UCY_StateBase>* pCurrentStateBase = EntireState.Find(CurrentStateId);

	return pCurrentStateBase ? *pCurrentStateBase : nullptr;
}

void UCY_StateMachine::GetActiveSceneId(TArray<int8>& ActiveSceneState) const
{
	if(EntireState.IsEmpty())
	{
		return;
	}
	
	ActiveSceneState.Empty();
	return EntireState.GenerateKeyArray(ActiveSceneState);
}

void UCY_StateMachine::SetState(int32 Index, bool _bInstant /* = true */)
{
	if(_bInstant)
	{
		SetState_Internal(Index);
	}
	else
	{
		ChangeStateId = Index;
	}
}

TObjectPtr<UCY_StateBase> UCY_StateMachine::GetState(int32 Index) const
{
	if(EntireState.Contains(Index))
	{
		return EntireState[Index];
	}

	return nullptr;
}

void UCY_StateMachine::SetState_Internal(uint8 Index)
{
	PreviousStateId = CurrentStateId;

	if(const TObjectPtr<UCY_StateBase> CurrentState = GetState(CurrentStateId))
	{
		CurrentState->OnExitState();
	}

	CurrentStateId = Index;

	if(const TObjectPtr<UCY_StateBase> NextState = GetState(Index))
	{
		NextState->OnBeginState();
	}
}
