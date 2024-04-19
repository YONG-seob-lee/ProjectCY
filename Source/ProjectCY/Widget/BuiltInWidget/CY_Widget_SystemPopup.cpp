// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_SystemPopup.h"

#include "Button/CY_DefaultButtonBase.h"
#include "Button/CY_ImageButton.h"
#include "Components/TextBlock.h"

void UCY_Widget_SystemPopup::ShowSystemPopup(const FCY_SystemPopupParameter& SystemPopupParam)
{
	SetVisibility(ESlateVisibility::Visible);
	
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

	if(CPP_ExitButton->IsVisible() && SystemPopupParam.OnClickExitDelegate.IsBound())
	{
		CPP_ExitButton->SetOnClickExitButton(SystemPopupParam.OnClickExitDelegate);
	}

	if(CPP_ConfirmButton->IsVisible() && SystemPopupParam.OnClickConfirmDelegate.IsBound())
	{
		CPP_ConfirmButton->SetOnClickButton(SystemPopupParam.OnClickConfirmDelegate);
	}

	if(CPP_CancelButton->IsVisible() && SystemPopupParam.OnClickCancelDelegate.IsBound())
	{
		CPP_CancelButton->SetOnClickButton(SystemPopupParam.OnClickCancelDelegate);
	}
}
