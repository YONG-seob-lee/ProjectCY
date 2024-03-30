﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Define.h"
#include "GameFramework/PlayerController.h"
#include "CY_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API ACY_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACY_PlayerController();
	virtual ~ACY_PlayerController() override;
	
	virtual void CreateTouchInterface() override;
	virtual void ActivateTouchInterface(UTouchInterface* NewTouchInterface) override;

	FORCEINLINE TObjectPtr<UTouchInterface> GetCurrentTouchInterface() const { return CurrentTouchInterface; }
	TObjectPtr<class SCY_VirtualJoyStick> GetVirtualJoyStick() const;
	
	FORCEINLINE void SetJoyStickVisualCenter(FVector2d Center) { JoyStickVisualCenter = Center; }
	FORCEINLINE FVector2d SetJoyStickVisualCenter() const { return JoyStickVisualCenter; }

	FORCEINLINE CY_Handle GetUnitHandle() const { return UnitHandle; }
	FORCEINLINE void SetUnitHandle(CY_Handle _UnitHandle) { UnitHandle = _UnitHandle; }
	FORCEINLINE void ResetUnitHandle() { UnitHandle = InvalidUnitHandle; }
	
private:
	CY_Handle UnitHandle = InvalidUnitHandle;
	
	FVector2d JoyStickVisualCenter = FVector2d();
};
