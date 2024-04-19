// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_WorldMapIcon.h"

#include "CY_WidgetManager.h"
#include "Button/CY_Button.h"
#include "Components/Image.h"

void UCY_Widget_WorldMapIcon::InitializeIcon()
{
	UCommonButtonBase::FCommonButtonEvent PressedEvent;
	PressedEvent.AddUObject(this, &UCY_Widget_WorldMapIcon::SetOnPressIcon);
	CPP_Button->SetOnPressedDelegate(PressedEvent);

	UCommonButtonBase::FCommonButtonEvent ReleasedEvent;
	ReleasedEvent.AddUObject(this, &UCY_Widget_WorldMapIcon::SetOnReleaseIcon);
	CPP_Button->SetOnClickedDelegate(ReleasedEvent);
}

void UCY_Widget_WorldMapIcon::SetIconTexture(TObjectPtr<UTexture2D> Texture) const
{
	CPP_IconImage->SetBrushFromTexture(Texture);
}

void UCY_Widget_WorldMapIcon::SetOnPressIcon()
{
	CPP_WidgetSwitcher->SetActiveWidgetIndex(ECY_IconSelectState::Select);
}

void UCY_Widget_WorldMapIcon::SetOnReleaseIcon()
{
	CPP_WidgetSwitcher->SetActiveWidgetIndex(ECY_IconSelectState::UnSelect);
	FCY_SystemPopupParameter Parameter;
	Parameter.TitleText = TEXT("확인");
	Parameter.bShowExitButton = true;
	Parameter.ContentsText = TEXT("");
	Parameter.SelectButtonState = ECY_SelectButtonState::OkCancel;
	Parameter.OnClickConfirmDelegate.AddWeakLambda(this, []()
	{
		// 드론 거꾸로 Fade 작동 및 해당 위치로 텔레포트
	});
	gWidgetMng.ShowSystemPopup(Parameter);
}
