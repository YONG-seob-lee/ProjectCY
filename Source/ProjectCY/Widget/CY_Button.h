// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CY_DefaultButton.h"
#include "CY_Button.generated.h"

/**
 *
 */
UCLASS(meta = (DisplayName = "CY BUTTON"))
class PROJECTCY_API UCY_Button : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UCY_Button();
	virtual ~UCY_Button() override;
	virtual void NativeConstruct() override;
	
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual const FText GetPaletteCategory() override;

	void SetText(const FString& ButtonString) const;

	void SetOnClickedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_OnClickedDelegate = Delegate; }
	FORCEINLINE void UnbindClickedDelegate() { CY_OnClickedDelegate.Clear(); }
	void SetOnPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_OnPressedDelegate = Delegate; }
	FORCEINLINE void UnbindPressedDelegate() { CY_OnPressedDelegate.Clear(); }
	void SetOnReleasedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_OnReleasedDelegate = Delegate; };
	FORCEINLINE void UnbindReleasedDelegate() { CY_OnReleasedDelegate.Clear(); }
	void SetOnHoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_OnHoveredDelegate = Delegate; };
	FORCEINLINE void UnbindHoveredDelegate() { CY_OnHoveredDelegate.Clear(); }
	void SetOnUnhoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_OnUnhoveredDelegate = Delegate; };
	FORCEINLINE void UnbindUnhoveredDelegate() { CY_OnUnhoveredDelegate.Clear(); }
	void SetWillCloseWidgetDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_WillCloseWidgetDelegate = Delegate; };
	FORCEINLINE void UnbindWillCloseWidgetDelegate() { CY_WillCloseWidgetDelegate.Clear(); }
	void SetWillCreateSceneDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_WillCreateSceneDelegate = Delegate; };
	FORCEINLINE void UnbindWillCreateSceneDelegate() { CY_WillCreateSceneDelegate.Clear(); }
	void SetPlayAnimDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_PlayAnimDelegate = Delegate; };
	FORCEINLINE void UnbindPlayAnimDelegate() { CY_PlayAnimDelegate.Clear(); }
	void SetOnClickedInDelayTimeDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_OnClickedInDelayTimeDelegate = Delegate; };
	FORCEINLINE void UnbindClickedInDelayTimeDelegate() { CY_OnClickedInDelayTimeDelegate.Clear(); }
	void SetOnLongPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); CY_OnLongPressedDelegate = Delegate; };
	FORCEINLINE void UnbindLongPressedDelegate() { CY_OnLongPressedDelegate.Clear(); }

private:
	void SetDelegates();
	
	UFUNCTION() void OnClick();
	UFUNCTION() void OnPress();
	UFUNCTION() void OnRelease();
	UFUNCTION() void OnHover();
	UFUNCTION() void OnUnhover();

	FORCEINLINE bool IsUseClockedDelay() const { return bUseClickedDelay && 0.f < ClickedDelayTime; }
	FORCEINLINE bool IsUseLongPressedEvent() const { return bUseLongPressedEvent && 0.f < LongPressedTime && GetWorld() != nullptr; }
protected:
	
	UPROPERTY(Category = UCY_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseClickedDelay = false;
	UPROPERTY(Category = UCY_Button, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseButtonText = true;
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

private:
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* CPP_CommonText = nullptr;
};