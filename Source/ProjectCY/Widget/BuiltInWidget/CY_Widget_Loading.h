// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_FadeCommand.h"
#include "CY_FadeSceneTool.h"
#include "CY_Widget.h"
#include "CY_Widget_Loading.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_Loading : public UCY_Widget
{
	GENERATED_BODY()
public:
	void SetLoadingData(ECY_LoadingPageType Ecy_LoadingPage);
	void ShowLoading();
};
