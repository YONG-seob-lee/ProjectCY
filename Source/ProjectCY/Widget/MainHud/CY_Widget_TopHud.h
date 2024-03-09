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
	

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudButton> CCY_TopHudButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpander> CCY_TopHudExpanderWidget = nullptr;
};

UCLASS()
class PROJECTCY_API UCY_Widget_TopHudButton : public UCY_Widget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Button> CCY_Button = nullptr;

};

UCLASS()
class PROJECTCY_API UCY_Widget_TopHudExpander : public UCY_Widget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpanderButton> CCY_ExpanderButton_0 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpanderButton> CCY_ExpanderButton_1 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpanderButton> CCY_ExpanderButton_2 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpanderButton> CCY_ExpanderButton_3 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpanderButton> CCY_ExpanderButton_4 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_TopHudExpanderButton> CCY_ExpanderButton_5 = nullptr;

};

UCLASS()
class PROJECTCY_API UCY_Widget_TopHudExpanderButton : public UCY_Widget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Button> CCY_ExpanderButton = nullptr;
};
