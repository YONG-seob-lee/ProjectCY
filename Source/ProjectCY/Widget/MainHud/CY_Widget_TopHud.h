// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/CY_Widget.h"
#include "CY_Widget_TopHud.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_TopHud : public UCY_Widget
{
	GENERATED_BODY()
public:
	void InitTopHudWidget();

	void OnClickTopHudButton();

	void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudButton> CPP_TopHudButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpander> CPP_TopHudExpanderWidget = nullptr;

	bool bIsOpenedExpander = false;
};

UCLASS()
class PROJECTCY_API UCY_Widget_TopHudButton : public UCY_Widget
{
	GENERATED_BODY()
public:
	void BindTopHudButtonEvent(const UCommonButtonBase::FCommonButtonEvent& Event) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_ImageButton> CPP_Button = nullptr;

};

UCLASS()
class PROJECTCY_API UCY_Widget_TopHudExpander : public UCY_Widget
{
	GENERATED_BODY()
public:
	
	virtual void NativeConstruct() override;

	void SetHudData();
	
private:
	void OnClickReturnTitleSceneButton();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> CPP_HorizontalBox = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpanderButton> CPP_ExpanderButton_0 = nullptr;
};

UCLASS()
class PROJECTCY_API UCY_Widget_TopHudExpanderButton : public UCY_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/Widget/MainHud/TopHudExpanderButton.TopHudExpanderButton")); }

	void BindExpanderButtonEvent(const UCommonButtonBase::FCommonButtonEvent& Event) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_ImageButton> CPP_ExpanderButton = nullptr;
};
