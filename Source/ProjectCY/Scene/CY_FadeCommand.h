// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneDefine.h"
#include "UObject/Object.h"
#include "CY_FadeCommand.generated.h"

DECLARE_DELEGATE(FCY_FadeEventDelegate);
/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_FadeCommand : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE ECY_FadeStyle GetFadeType() const { return Fade; }
	FORCEINLINE bool GetIsDirectFadeIn() const { return bDirectFadeIn; }
	FORCEINLINE ECY_LoadingPageType GetLoadingPageType() const { return LoadingPageType; }

	FCY_FadeEventDelegate OnFadeInComplete;
	FCY_FadeEventDelegate OnFadeOutComplete;
	FCY_FadeEventDelegate OnFadeOutStart;
private:
	ECY_FadeStyle Fade = ECY_FadeStyle::None;
	ECY_LoadingPageType LoadingPageType = ECY_LoadingPageType::None;
	bool bDirectFadeIn = false;
};
