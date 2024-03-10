// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_StateBase.h"
#include "CY_StateMachine.h"

void UCY_StateBase::Initialize(uint8 Index, const FName& Name)
{
	StateIndex = Index;
	StateName = Name;
}

void UCY_StateBase::Finalize()
{
}

void UCY_StateBase::OnBeginState()
{
	Begin();
}

void UCY_StateBase::OnTickState()
{
	//Tick();
}

void UCY_StateBase::OnExitState()
{
	Exit();
}

TObjectPtr<UCY_StateMachine> UCY_StateBase::GetStateMachine()
{
	return Cast<UCY_StateMachine>(GetOuter());
}
