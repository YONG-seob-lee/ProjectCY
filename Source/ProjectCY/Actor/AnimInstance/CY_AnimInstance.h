// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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


private:
	float MovingSpeed = 0.f;
};
