// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneDefine.h"
#include "CY_Widget.h"
#include "CY_Widget_DialogScreenFader.generated.h"

DECLARE_DELEGATE(FBuiltInFadeDelegate);
DECLARE_MULTICAST_DELEGATE(FBuiltInFadeOutComplete);
DECLARE_MULTICAST_DELEGATE(FBuiltInFadeInComplete);

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_DialogScreenFader : public UCY_Widget
{
	GENERATED_BODY()

public:
	void StartScreenFade(ECY_FadeType _FadeType, FBuiltInFadeDelegate FadeInCallback = nullptr, FBuiltInFadeDelegate FadeOutCallback = nullptr);


private:
	ECY_FadeType FadeType;
	ECY_FadeStatus FadeStatus;
	FBuiltInFadeInComplete FadeInCompleteCallback;
	FBuiltInFadeOutComplete FadeOutCompleteCallback;
};
