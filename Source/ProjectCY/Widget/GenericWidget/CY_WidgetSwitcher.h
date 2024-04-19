// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "CY_WidgetSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_WidgetSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()
public:
	virtual void SetActiveWidgetIndex(int32 Index) override;

private:
	UPROPERTY(Category = UCY_WidgetSwitcher, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bUseWidgetSwitchDelay = false;

	UPROPERTY(Category = UCY_WidgetSwitcher, EditAnywhere, meta = (AllowPrivateAccess = "true", EditCondition = "bUseWidgetSwitchDelay"))
	float SwitchDelayTime = 0.f;

	float LastSwitchTime = 0.f;
};
