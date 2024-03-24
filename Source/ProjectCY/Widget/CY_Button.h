// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CY_Define.h"
#include "CY_Button.generated.h"

/**
 *
 */
UCLASS(meta = (DisplayName = "CY BUTTON"))
class PROJECTCY_API UCY_Button : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	void SetOnClickedDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_OnClickedDelegate = p_delegate; };
	FORCEINLINE void UnbindClickedDelegate() { CY_OnClickedDelegate.Clear(); }
	void SetOnPressedDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_OnPressedDelegate = p_delegate; };
	FORCEINLINE void UnbindPressedDelegate() { CY_OnPressedDelegate.Clear(); }
	void SetOnReleasedDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_OnReleasedDelegate = p_delegate; };
	FORCEINLINE void UnbindReleasedDelegate() { CY_OnReleasedDelegate.Clear(); }
	void SetOnHoveredDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_OnHoveredDelegate = p_delegate; };
	FORCEINLINE void UnbindHoveredDelegate() { CY_OnHoveredDelegate.Clear(); }
	void SetOnUnhoveredDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_OnUnhoveredDelegate = p_delegate; };
	FORCEINLINE void UnbindUnhoveredDelegate() { CY_OnUnhoveredDelegate.Clear(); }
	void SetWillCloseWidgetDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_WillCloseWidgetDelegate = p_delegate; };
	FORCEINLINE void UnbindWillCloseWidgetDelegate() { CY_WillCloseWidgetDelegate.Clear(); }
	void SetWillCreateSceneDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_WillCreateSceneDelegate = p_delegate; };
	FORCEINLINE void UnbindWillCreateSceneDelegate() { CY_WillCreateSceneDelegate.Clear(); }
	void SetPlayAnimDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_PlayAnimDelegate = p_delegate; };
	FORCEINLINE void UnbindPlayAnimDelegate() { CY_PlayAnimDelegate.Clear(); }
	void SetOnClickedInDelayTimeDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_OnClickedInDelayTimeDelegate = p_delegate; };
	FORCEINLINE void UnbindClickedInDelayTimeDelegate() { CY_OnClickedInDelayTimeDelegate.Clear(); }
	void SetOnLongPressedDelegate(FCommonButtonEvent p_delegate) { SetDelegates(); CY_OnLongPressedDelegate = p_delegate; };
	FORCEINLINE void UnbindLongPressedDelegate() { CY_OnLongPressedDelegate.Clear(); }

private:
	void SetDelegates();

	
	UFUNCTION() void OnClick();
	UFUNCTION() void OnPress();
	UFUNCTION() void OnReleas();
	UFUNCTION() void OnHover();
	UFUNCTION() void OnUnhover();

	FORCEINLINE bool IsUseClockedDelay() { return bUseClickedDelay && 0.f < ClickedDelayTime; }
	FORCEINLINE bool IsUseLongPressedEvent() { return bUseLongPressedEvent && 0.f < LongPressedTime && GetWorld() != nullptr; }
protected:
	UPROPERTY(Category = UCY_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseClickedDelay = false;
	UPROPERTY(Category = UCY_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseClickedDelay"))
	float ClickedDelayTime = 0.f;
	UPROPERTY(Category = UCY_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseReleasedDelay = false;
	UPROPERTY(Category = UCY_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseReleasedDelay"))
	float ReleasedDelayTime = 0.f;
	UPROPERTY(Category = UCY_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseLongPressedEvent = false;
	UPROPERTY(Category = UCY_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseLongPressedEvent"))
	float LongPressedTime = 0.f;
	
	FCommonButtonEvent CY_OnClickedDelegate;
	FCommonButtonEvent CY_OnPressedDelegate;
	FCommonButtonEvent CY_OnReleasedDelegate;
	FCommonButtonEvent CY_OnHoveredDelegate;
	FCommonButtonEvent CY_OnUnhoveredDelegate;

	FCommonButtonEvent CY_OnClickedInDelayTimeDelegate;
	FCommonButtonEvent CY_OnLongPressedDelegate;

	FCommonButtonEvent CY_PlayAnimDelegate;
	FCommonButtonEvent CY_WillCloseWidgetDelegate;
	FCommonButtonEvent CY_WillCreateSceneDelegate;

	float LastClickedTime = 0.f;
	float LastReleasedTime = 0.f;
};