// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CY_Define.h"
#include "CY_Button.generated.h"

/**
 *
 */
UCLASS(meta = (DisplayName = "CY BUTTON"))
class PROJECTCY_API UCY_Button : public UButton
{
	GENERATED_BODY()

public:

	void SetOnClickedDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); OnClickedDelegate = p_delegate; };
	FORCEINLINE void UnbindClickedDelegate() { OnClickedDelegate.Unbind(); }
	void SetOnPressedDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); OnPressedDelegate = p_delegate; };
	FORCEINLINE void UnbindPressedDelegate() { OnPressedDelegate.Unbind(); }
	void SetOnReleasedDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); OnReleasedDelegate = p_delegate; };
	FORCEINLINE void UnbindReleasedDelegate() { OnReleasedDelegate.Unbind(); }
	void SetOnHoveredDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); OnHoveredDelegate = p_delegate; };
	FORCEINLINE void UnbindHoveredDelegate() { OnHoveredDelegate.Unbind(); }
	void SetOnUnhoveredDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); OnUnhoveredDelegate = p_delegate; };
	FORCEINLINE void UnbindUnhoveredDelegate() { OnUnhoveredDelegate.Unbind(); }
	void SetWillCloseWidgetDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); WillCloseWidgetDelegate = p_delegate; };
	FORCEINLINE void UnbindWillCloseWidgetDelegate() { WillCloseWidgetDelegate.Unbind(); }
	void SetWillCreateSceneDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); WillCreateSceneDelegate = p_delegate; };
	FORCEINLINE void UnbindWillCreateSceneDelegate() { WillCreateSceneDelegate.Unbind(); }
	void SetPlayAnimDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); PlayAnimDelegate = p_delegate; };
	FORCEINLINE void UnbindPlayAnimDelegate() { PlayAnimDelegate.Unbind(); }
	void SetOnClickedInDelayTimeDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); OnClickedInDelayTimeDelegate = p_delegate; };
	FORCEINLINE void UnbindClickedInDelayTimeDelegate() { OnClickedInDelayTimeDelegate.Unbind(); }
	void SetOnLongPressedDelegate(FButtonEventDelegate p_delegate) { SetDelegates(); OnLongPressedDelegate = p_delegate; };
	FORCEINLINE void UnbindLongPressedDelegate() { OnLongPressedDelegate.Unbind(); }

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

	FButtonEventDelegate OnClickedDelegate;
	FButtonEventDelegate OnPressedDelegate;
	FButtonEventDelegate OnReleasedDelegate;
	FButtonEventDelegate OnHoveredDelegate;
	FButtonEventDelegate OnUnhoveredDelegate;

	FButtonEventDelegate OnClickedInDelayTimeDelegate;
	FButtonEventDelegate OnLongPressedDelegate;

	FButtonEventDelegate PlayAnimDelegate;
	FButtonEventDelegate WillCloseWidgetDelegate;
	FButtonEventDelegate WillCreateSceneDelegate;

	float LastClickedTime = 0.f;
	float LastReleasedTime = 0.f;
};