// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_SystemPopup.h"

#include "Button/CY_DefaultButton.h"
#include "Button/CY_ImageButton.h"
#include "Components/TextBlock.h"

void UCY_Widget_SystemPopup::ShowSystemPopup(const FCY_SystemPopupParameter& SystemPopupParam)
{
	if(CPP_PopupTitleText)
	{
		CPP_PopupTitleText->SetText(FText::FromString(SystemPopupParam.TitleText));
	}

	if(CPP_ExitButton)
	{
		CPP_ExitButton->SetVisibility(SystemPopupParam.bShowExitButton ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}

	if(CPP_ContentsText)
	{
		CPP_ContentsText->SetText(FText::FromString(SystemPopupParam.ContentsText));
	}

	if(CPP_ConfirmButton && CPP_CancelButton)
	{
		switch(SystemPopupParam.SelectButtonState)
		{
		case ECY_SelectButtonState::OkCancel:
			CPP_ConfirmButton->SetVisibility(ESlateVisibility::Visible);
			CPP_CancelButton->SetVisibility(ESlateVisibility::Visible);
			break;
		case ECY_SelectButtonState::Ok:
			CPP_ConfirmButton->SetVisibility(ESlateVisibility::Visible);
			CPP_CancelButton->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case ECY_SelectButtonState::Cancel:
			CPP_ConfirmButton->SetVisibility(ESlateVisibility::Collapsed);
			CPP_CancelButton->SetVisibility(ESlateVisibility::Visible);
			break;
		default:
			CPP_ConfirmButton->SetVisibility(ESlateVisibility::Collapsed);
			CPP_CancelButton->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}	
	}

	if(SystemPopupParam.OnClickExitEvent.IsBound() == false)
	{
		UCommonButtonBase::FCommonButtonEvent ExitEvent;
		ExitEvent.AddWeakLambda(this, [this]()
		{
			CloseWidget();
		});
		CPP_ExitButton->SetOnClickExitButton(ExitEvent);
	}
	else
	{
		CPP_ExitButton->SetOnClickExitButton(SystemPopupParam.OnClickExitEvent);
	}

	if(CPP_ConfirmButton->IsVisible() && SystemPopupParam.OnClickConfirmEvent.IsBound())
	{
		CPP_ConfirmButton->SetOnClickButton(SystemPopupParam.OnClickConfirmEvent);
	}

	if(CPP_CancelButton->IsVisible() && SystemPopupParam.OnClickCancelEvent.IsBound())
	{
		CPP_CancelButton->SetOnClickButton(SystemPopupParam.OnClickCancelEvent);
	}
}
