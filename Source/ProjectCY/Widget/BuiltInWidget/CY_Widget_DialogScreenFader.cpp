// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_DialogScreenFader.h"

namespace FadeType
{
	const FName FadeIn = TEXT("FadeIn");
	const FName FadeOut = TEXT("FadeOut");
}

void UCY_Widget_DialogScreenFader::StartScreenFade(ECY_FadeType _FadeType, FBuiltInFadeDelegate FadeInCallback, FBuiltInFadeDelegate FadeOutCallback)
{
	FadeInCompleteCallback.Clear();
	FadeOutCompleteCallback.Clear();

	if(FadeInCallback.IsBound())
	{
		FadeInCompleteCallback.Add(FadeInCallback);
	}
	if(FadeOutCallback.IsBound())
	{
		FadeOutCompleteCallback.Add(FadeOutCallback);
	}

	SetVisibility(ESlateVisibility::Visible);

	FadeType = _FadeType;
	if(FadeType == ECY_FadeType::FadeIn)
	{
		FadeStatus = ECY_FadeStatus::FadeInAnimation;
		PlayAnimationByName(FadeType::FadeIn);
	}
	else if(FadeType == ECY_FadeType::FadeOut)
	{
		FadeStatus = ECY_FadeStatus::FadeOutAnimation;
		PlayAnimationByName(FadeType::FadeOut);
	}
}
