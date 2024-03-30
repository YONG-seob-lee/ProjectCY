﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Singleton.h"
#include "UObject/Object.h"
#include "CY_InputManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_InputManager : public UObject, public UCY_Singleton<UCY_InputManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	void RegistAxis(ECY_Axis_Type AxisType, ECY_Action_Type ActionType, const FInputAxisUnifiedDelegate& Event);
	void RegistTouch(ECY_Touch_Event TouchEventType, const FInputTouchBinding& Event);
	void RegistAndroidButton(ECY_AndroidButton_Type ButtonType, const FSimpleDelegate& Delegate);
	
	void CreateInputPawn();
	void DestroyInputPawn();

	FORCEINLINE FBindAllKeysDelegate& GetBindAllKeysDelegate() { return AllKeysDelegate; }

private:
	UPROPERTY()
	TObjectPtr<class ACY_Pawn_Input> InputPawn = nullptr;

	FBindAllKeysDelegate AllKeysDelegate;

// todo : 용섭 Input Mapping Part
	
public:
	void LeftAxisUpDown(float Value);
	void LeftAxisLeftRight(float Value);
	void OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchUp(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchMove(const ETouchIndex::Type FingerIndex, const FVector Location);
	void AndroidBack();
	void AndroidMenu();

private:
	FInputAxisBinding UpDownEvent = FInputAxisBinding(TEXT("UpDown"));
	FInputAxisBinding LeftRightEvent = FInputAxisBinding(TEXT("LeftRight"));
	FInputTouchBinding TouchDownEvent = FInputTouchBinding(IE_Pressed);
	FInputTouchBinding TouchUpEvent = FInputTouchBinding(IE_Released);
	FInputTouchBinding TouchMoveEvent = FInputTouchBinding(IE_Repeat);
	FSimpleDelegate AndroidBackDelegate;
	FSimpleDelegate AndroidMenuDelegate;
	
#define gInputMng (*UCY_InputManager::GetInstance())
};
