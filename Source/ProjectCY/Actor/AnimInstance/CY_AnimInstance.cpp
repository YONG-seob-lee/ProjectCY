// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_AnimInstance.h"

void UCY_AnimInstance::Initialize()
{
	MovingSpeed = 0.f;
	MaxWalkSpeed = 0.f;
	MaxRunSpeed = 0.f;
	PreviousMovingSpeed = 0.f;
	MovingEndSpeed = 0.f;
}

void UCY_AnimInstance::Finalize()
{
	MovingSpeed = 0.f;
}

void UCY_AnimInstance::SetMoveSpeed(float MoveSpeed)
{
	if(FMath::IsNearlyZero(MoveSpeed) == true && FMath::IsNearlyZero(PreviousMovingSpeed) == false)
	{
		MovingEndSpeed = PreviousMovingSpeed;
	}

	PreviousMovingSpeed = MovingSpeed;
	MovingSpeed = MoveSpeed;
}
