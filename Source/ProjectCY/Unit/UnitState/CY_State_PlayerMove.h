// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_StateBase.h"
#include "CY_State_PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_State_PlayerMove : public UCY_StateBase
{
	GENERATED_BODY()
public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

private:
	void PlayerMove();

	float WalkSpeed = 0.f;
	float RunSpeed = 0.f;
	
	
	void OnAxisUpDown(float AxisValue);
	void OnAxisLeftRight(float AxisValue);
	
	TObjectPtr<class UCY_BasePlayer> OwnerUnit = nullptr;
	TObjectPtr<class ACY_CameraActor> CameraActor = nullptr;
	FVector2d JoyStickDistance = FVector2d::ZeroVector;
	
	FVector CachedUnitForward = FVector::ZeroVector;
	FVector CachedUnitRight = FVector::ZeroVector;
};
