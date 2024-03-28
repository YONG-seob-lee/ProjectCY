// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_DialogScreenFader.h"

namespace FadeType
{
	const FName FadeIn = TEXT("FadeIn");
	const FName FadeOut = TEXT("FadeOut");
}

void UCY_Widget_DialogScreenFader::StartScreenFade(ECY_FadeType _FadeType, const TFunction<void()>& FadeCallback /* = nullptr */)
{
	FadeInCompleteCallback = nullptr;
	FadeOutCompleteCallback = nullptr;

	if(_FadeType == ECY_FadeType::FadeIn)
	{
		FadeInCompleteCallback = FadeCallback;
	}
	else if(_FadeType == ECY_FadeType::FadeOut)
	{
		FadeOutCompleteCallback = FadeCallback;
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

void UCY_Widget_DialogScreenFader::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == FadeType::FadeIn)
	{
		FinishedFadeIn();
	}
	else if(AnimName == FadeType::FadeOut)
	{
		FinishedFadeOut();
	}
}

void UCY_Widget_DialogScreenFader::FinishedFadeIn() const
{
	if(FadeInCompleteCallback)
	{
		FadeInCompleteCallback();
	}
	CY_LOG(TEXT("FadeIn Finished"));
}

void UCY_Widget_DialogScreenFader::FinishedFadeOut()
{
	if(FadeOutCompleteCallback)
	{
		FadeOutCompleteCallback();
	}
	CY_LOG(TEXT("FadeOut Finished"));
	
	SetVisibility(ESlateVisibility::Collapsed);
}
