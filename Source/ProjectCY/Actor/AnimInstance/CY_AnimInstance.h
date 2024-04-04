// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource_Unit.h"
#include "Animation/AnimInstance.h"
#include "CY_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	void Initialize();
	void Finalize();

	FORCEINLINE float GetMovingSpeed() const { return MovingSpeed; }

	void SetMoveSpeed(float MoveSpeed);
	FORCEINLINE void SetMoveSpeedInfo(float _WalkSpeed, float _RunSpeed, float _FastRunSpeed = 0.f)
	{
		MaxWalkSpeed = _WalkSpeed;
		MaxRunSpeed = _RunSpeed;
		MaxFastRunSpeed = _FastRunSpeed == 0.f ? _RunSpeed : _FastRunSpeed;
	}

private:
	UPROPERTY(Category = CY_AnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MovingSpeed = 0.f;

	UPROPERTY(Category = CY_AnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeed = 0.f;

	UPROPERTY(Category = CY_AnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxRunSpeed = 0.f;

	UPROPERTY(Category = CY_AnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxFastRunSpeed = 0.f;
	
	UPROPERTY(Category = CY_AnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float PreviousMovingSpeed = 0.f;

	UPROPERTY(Category = CY_AnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MovingEndSpeed = 0.f;
};
