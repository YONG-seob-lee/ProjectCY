// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_StateBase.h"
#include "CY_State_PlayerNormal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_State_PlayerNormal : public UCY_StateBase
{
	GENERATED_BODY()
public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

	void SetOnInteractionEventFunc(const TFunction<void()>& _Func) { OnInteractionCallback = _Func; }
	
private:
	void PlayerMove();
	
	void InteractionProcess();	
	
	void OnAxisUpDown(float AxisValue);
	void OnAxisLeftRight(float AxisValue);

	void OnClickInteraction();
	void OnClickWorldMap();

	
	TObjectPtr<class UCY_BasePlayer> OwnerUnit = nullptr;
	TObjectPtr<class ACY_CameraActor> CameraActor = nullptr;

	float WalkSpeed = 0.f;
	float RunSpeed = 0.f;
	float SprintSpeed = 0.f;
	
	FVector2d JoyStickDistance = FVector2d::ZeroVector;
	FVector CachedUnitForward = FVector::ZeroVector;
	FVector CachedUnitRight = FVector::ZeroVector;

	TFunction<void()> OnInteractionCallback = nullptr;
};
