// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_Toast.h"

#include "Components/TextBlock.h"

void UCY_Widget_Toast::ShowToast(const FString& Message)
{
	CPP_MessageText->SetText(FText::FromString(Message));

	Active();
}

void UCY_Widget_Toast::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == DefaultWidgetAnimation::Appearance)
	{
		StopAllAnimations();
		PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
	}
	else if(AnimName == DefaultWidgetAnimation::DisAppearance)
	{
		StopAllAnimations();
		Active(false);
	}
}
