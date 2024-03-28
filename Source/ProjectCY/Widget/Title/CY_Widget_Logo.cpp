// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_Logo.h"

#include "CY_Button.h"
#include "CY_SceneManager.h"

void UCY_Widget_Logo::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	UCommonButtonBase::FCommonButtonEvent Event;
	Event.AddUObject(this, &UCY_Widget_Logo::OnClickBlankButton);
	CPP_BlankButton->SetOnClickedDelegate(Event);
}

void UCY_Widget_Logo::FinishWidget()
{
	CPP_BlankButton->UnbindClickedDelegate();
	Super::FinishWidget();
}

void UCY_Widget_Logo::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if(Animation == GetAnimationByName(DefaultWidgetAnimation::Appearance))
	{
		PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
		CPP_BlankButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(Animation == GetAnimationByName(DefaultWidgetAnimation::DisAppearance))
	{
		gSceneMng.ChangeScene(ECY_GameSceneType::Title);
	}
}

void UCY_Widget_Logo::OnClickBlankButton()
{
	if(IsPlayingAnimation())
	{
		StopAllAnimations();
	}
}
