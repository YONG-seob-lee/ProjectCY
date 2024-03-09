// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_MainHud.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_MainHud : public UCY_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_MainHud> CCY_TopHudWidget = nullptr;
};
