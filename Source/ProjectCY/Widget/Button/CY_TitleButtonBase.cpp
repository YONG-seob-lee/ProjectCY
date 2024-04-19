// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_TitleButtonBase.h"

#include "CY_Button.h"
#include "CommonTextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UCY_TitleButtonBase::NativeConstruct()
{
	if(IsValid(TextStyle))
	{
		CPP_CommonText->SetStyle(TextStyle);
	}
	
	CPP_Text_Panel->SetVisibility(bUseButtonText ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	CPP_CommonText->SetVisibility(bUseButtonText ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}

void UCY_TitleButtonBase::NativeDestruct()
{
}

void UCY_TitleButtonBase::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UCY_TitleButtonBase::FinishWidget()
{
	Super::FinishWidget();

	CPP_ButtonBase->UnbindClickedDelegate();
}

void UCY_TitleButtonBase::SetOnClickEvent(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	CPP_ButtonBase->SetOnClickedDelegate(Event);
}

void UCY_TitleButtonBase::UnbindClickEvent() const
{
	CPP_ButtonBase->UnbindClickedDelegate();
}

void UCY_TitleButtonBase::SetButtonText(const FString& ButtonText) const
{
	if(CPP_ButtonBase)
	{
		CPP_CommonText->SetText(FText::FromString(ButtonText));
	}
}

void UCY_TitleButtonBase::SetText(const FString& ButtonString) const
{
	if(CPP_Text_Panel && CPP_CommonText)
	{
		CPP_CommonText->SetText(FText::FromString(ButtonString));
	}
}

void UCY_TitleButtonBase::SetOnClickedDelegate(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	if(CPP_ButtonBase)
	{
		CPP_ButtonBase->SetOnClickedDelegate(Event);
	}
}

void UCY_TitleButtonBase::SetStyleChange(TSubclassOf<UCommonTextStyle> _TextStyle) const
{
	if(CPP_CommonText)
	{
		CPP_CommonText->SetStyle(_TextStyle);
	}
}

void UCY_TitleButtonBase::OnClicked()
{
}
