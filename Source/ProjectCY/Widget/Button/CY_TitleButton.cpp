// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_TitleButton.h"

#include "CY_Button.h"
#include "CommonTextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UCY_TitleButton::NativeConstruct()
{
	CPP_CommonText->SetStyle(TextStyle);
	
	CPP_Text_Panel->SetVisibility(bUseButtonText ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	CPP_CommonText->SetVisibility(bUseButtonText ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}

void UCY_TitleButton::NativeDestruct()
{
}

void UCY_TitleButton::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UCY_TitleButton::FinishWidget()
{
	Super::FinishWidget();

	CPP_ButtonBase->UnbindClickedDelegate();
}

void UCY_TitleButton::SetOnClickEvent(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	CPP_ButtonBase->SetOnClickedDelegate(Event);
}

void UCY_TitleButton::UnbindClickEvent() const
{
	CPP_ButtonBase->UnbindClickedDelegate();
}

void UCY_TitleButton::SetButtonText(const FString& ButtonText) const
{
	if(CPP_ButtonBase)
	{
		CPP_CommonText->SetText(FText::FromString(ButtonText));
	}
}

void UCY_TitleButton::SetText(const FString& ButtonString) const
{
	if(CPP_Text_Panel && CPP_CommonText)
	{
		CPP_CommonText->SetText(FText::FromString(ButtonString));
	}
}

void UCY_TitleButton::SetOnClickedDelegate(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	if(CPP_ButtonBase)
	{
		CPP_ButtonBase->SetOnClickedDelegate(Event);
	}
}

void UCY_TitleButton::SetStyleChange(TSubclassOf<UCommonTextStyle> _TextStyle) const
{
	if(CPP_CommonText)
	{
		CPP_CommonText->SetStyle(_TextStyle);
	}
}

void UCY_TitleButton::OnClicked()
{
}
