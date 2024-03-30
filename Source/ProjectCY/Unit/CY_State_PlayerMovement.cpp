// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_State_PlayerMovement.h"

#include "CY_BasePlayer.h"
#include "CY_InputManager.h"
#include "Resource_Unit.h"

void UCY_State_PlayerMovement::Begin()
{
	OwnerUnit = CastChecked<UCY_BasePlayer>(GetOuter());

	FInputAxisUnifiedDelegate UpDownDelegate;
	UpDownDelegate.BindDelegate(this, &UCY_State_PlayerMovement::OnAxisUpDown);
	gInputMng.RegistAxis(ECY_Axis_Type::Left, ECY_Action_Type::ActionUpDown, UpDownDelegate);

	FInputAxisUnifiedDelegate LeftRightDelegate;
	LeftRightDelegate.BindDelegate(this, &UCY_State_PlayerMovement::OnAxisLeftRight);
	gInputMng.RegistAxis(ECY_Axis_Type::Left, ECY_Action_Type::ActionLeftRight, LeftRightDelegate);
}

void UCY_State_PlayerMovement::Tick(float DeltaTime)
{
	if(OwnerUnit)
	{
		UnitMoveProcess(DeltaTime);
	}
}

void UCY_State_PlayerMovement::Exit()
{
	Super::Exit();
}

void UCY_State_PlayerMovement::UnitMoveProcess(float Delta)
{
	const float DetectJoyStickValue = JoyStickDistance.Size();
	float MoveSpeed = 0.f;

	const TObjectPtr<ACY_CharacterBase> Character = OwnerUnit->GetCharacterBase();
	if(Character == nullptr)
	{
		return;
	}
	
	if(DetectJoyStickValue > 0.01f)
	{
		if(Character->IsMovePathFindingPoints())
		{
			Character->ClearPathFindPoints();
		}

		if(DetectJoyStickValue < 0.5f)
		{
			MoveSpeed = OwnerUnit->GetResourceUnitData()->WalkSpeed;
		}
		else
		{
			MoveSpeed = OwnerUnit->GetResourceUnitData()->RunSpeed;
		}
	}
	else
	{
		if(Character->IsMovePathFindingPoints())
		{
			MoveSpeed = OwnerUnit->GetResourceUnitData()->RunSpeed;
		}
	}
	
	OwnerUnit->SetMoveSpeed(MoveSpeed);
	JoyStickDistance.X = JoyStickDistance.Y = 0.f;
}

void UCY_State_PlayerMovement::OnAxisUpDown(float Value)
{
	if(FMath::IsNearlyEqual(Value, 0.f) == false)
	{
		JoyStickDistance.Y = Value;
	}
}

void UCY_State_PlayerMovement::OnAxisLeftRight(float Value)
{
	if(FMath::IsNearlyEqual(Value, 0.f) == false)
	{
		JoyStickDistance.X = Value;
	}
}
