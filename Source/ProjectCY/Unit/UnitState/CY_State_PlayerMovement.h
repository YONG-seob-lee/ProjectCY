// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_StateBase.h"
#include "CY_State_PlayerMovement.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_State_PlayerMovement : public UCY_StateBase
{
	GENERATED_BODY()
public:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

	FORCEINLINE void SetEnableInput(bool bEnable) { bEnableInput = bEnable; }
	FORCEINLINE bool GetEnableInput() const { return bEnableInput;}
	
private:
	void UnitMoveProcess();

	void OnAxisUpDown(float Value);
	void OnAxisLeftRight(float Value);

	TObjectPtr<class UCY_BasePlayer> OwnerUnit = nullptr;
	bool bEnableInput = false;

	FVector2d JoyStickDistance = FVector2d::ZeroVector;
};
