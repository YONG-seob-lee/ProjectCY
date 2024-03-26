// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_Touch.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_Touch : public UCY_Widget
{
	GENERATED_BODY()
public:
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;
	
	void TouchEvent();
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNiagaraSystemWidget> CPP_TouchEffectWidget = nullptr;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Touch_Anim = nullptr;
};
