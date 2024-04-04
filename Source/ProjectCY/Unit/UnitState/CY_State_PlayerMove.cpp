// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_State_PlayerMove.h"

#include "CY_BasePlayer.h"
#include "CY_BasicGameUtility.h"
#include "CY_CameraActor.h"
#include "CY_CameraManager.h"
#include "CY_InputManager.h"
#include "Resource_Unit.h"

void UCY_State_PlayerMove::Begin()
{
	OwnerUnit = CastChecked<UCY_BasePlayer>(GetOuter());
	if(OwnerUnit == nullptr)
	{
		return;
	}

	WalkSpeed = OwnerUnit->GetResourceUnitData()->WalkSpeed;
	RunSpeed = OwnerUnit->GetResourceUnitData()->RunSpeed;

	FInputAxisUnifiedDelegate UpDownDelegate;
	UpDownDelegate.BindDelegate(this, &UCY_State_PlayerMove::OnAxisUpDown);
	gInputMng.RegistAxis(ECY_Axis_Type::Left, ECY_Action_Type::ActionUpDown, UpDownDelegate);

	FInputAxisUnifiedDelegate LeftRightDelegate;
	LeftRightDelegate.BindDelegate(this, &UCY_State_PlayerMove::OnAxisLeftRight);
	gInputMng.RegistAxis(ECY_Axis_Type::Left, ECY_Action_Type::ActionLeftRight, LeftRightDelegate);
}

void UCY_State_PlayerMove::Tick(float DeltaTime)
{
	if(CameraActor == nullptr)
	{
		CameraActor = gCameraMng.GetCurrentActiveCameraActor();
	}
	
	if(OwnerUnit)
	{
		PlayerMove();
	}
}

void UCY_State_PlayerMove::Exit()
{
	Super::Exit();
}

void UCY_State_PlayerMove::PlayerMove()
{
	const TObjectPtr<ACY_CharacterBase> Character = OwnerUnit->GetCharacterBase();
	if(Character == nullptr)
	{
		return;
	}

	const float DetectJoyStickValue = JoyStickDistance.Size();

	// Step 1. 카메라의 정면벡터가 캐릭터의 정면벡터가 될 수 있게 캐싱
	if(CameraActor == nullptr)
	{
		return;
	}
		
	if(CachedUnitForward == FVector::ZeroVector || CachedUnitRight == FVector::ZeroVector)
	{
		CachedUnitForward = CameraActor->GetForward();
		CachedUnitRight= CameraActor->GetCross();
	}
	
	// Step 2. 캐릭터 정면벡터와 조이스틱을 바인딩
	if(DetectJoyStickValue > 0.001f)
	{
		FVector NewMoveDirection = JoyStickDistance.Y * CachedUnitForward + JoyStickDistance.X * CachedUnitRight;
		CY_LOG(TEXT("%f"), NewMoveDirection.Size());
		NewMoveDirection.Z = 0.f;
		
		FRotator Rotator = NewMoveDirection.Rotation();
		
		// 시계, 반시계
		
		NewMoveDirection.Normalize();
		
		OwnerUnit->SetMoveSpeed(DetectJoyStickValue <= 0.5f ? WalkSpeed : RunSpeed);
		Character->MoveDirection(NewMoveDirection);
	}
	// Step 3. 캐릭터가 더이상 움직이지 않으면 캐싱데이터 제거 및 캐릭터 속도 0 ( 나중에 속도 감쇠 기능 추가해야할 듯 싶음 - 캐릭터 방향성 래깅도 필요해보임)
	else
	{
		CachedUnitForward = FVector::ZeroVector;
		CachedUnitRight = FVector::ZeroVector;
		OwnerUnit->SetMoveSpeed(0.f);
	}
	JoyStickDistance = FVector2d::ZeroVector;
}

void UCY_State_PlayerMove::OnAxisUpDown(float AxisValue)
{
	if(FMath::IsNearlyEqual(AxisValue, 0.f) == false)
	{
		JoyStickDistance.Y = AxisValue;
	}
}

void UCY_State_PlayerMove::OnAxisLeftRight(float AxisValue)
{
	if(FMath::IsNearlyEqual(AxisValue, 0.f) == false)
	{
		JoyStickDistance.X = AxisValue;
	}
}
