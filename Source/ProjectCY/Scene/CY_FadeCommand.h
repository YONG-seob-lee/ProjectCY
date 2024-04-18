// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneDefine.h"
#include "UObject/Object.h"
#include "CY_FadeCommand.generated.h"

DECLARE_DELEGATE(FCY_FadeEventDelegate);
DECLARE_DELEGATE_RetVal(bool, FCY_FadeCheckLoadDelegate);

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_FadeCommand : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetFadeStyle(ECY_FadeStyle FadeStyle) { Fade = FadeStyle; }
	FORCEINLINE void SetIsDirectFadeOut(bool _bDirectFadeOut) { bDirectFadeOut = _bDirectFadeOut; }
	FORCEINLINE void SetLoadingPageType(ECY_LoadingPageType Type) { LoadingPageType = Type; }
	
	FORCEINLINE ECY_FadeStyle GetFadeType() const { return Fade; }
	FORCEINLINE bool GetIsDirectFadeOut() const { return bDirectFadeOut; }
	FORCEINLINE ECY_LoadingPageType GetLoadingPageType() const { return LoadingPageType; }
	
	FCY_FadeEventDelegate OnFadeOutComplete;
	FCY_FadeEventDelegate OnFadeInStart;
	FCY_FadeEventDelegate OnFadeInComplete;

	FCY_FadeCheckLoadDelegate OnCheckLoadComplete;
	
	void SetCreateFrom(const ANSICHAR* File, const int32 Line);
private:
	ECY_FadeStyle Fade = ECY_FadeStyle::None;
	ECY_LoadingPageType LoadingPageType = ECY_LoadingPageType::None;
	bool bDirectFadeOut = false;
	
	FString CreateFileLine = FString();
};
