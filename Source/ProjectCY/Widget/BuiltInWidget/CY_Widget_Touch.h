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

	void PlayTouch() const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNiagaraSystemWidget> CCY_TouchEffectWidget = nullptr;
};
