// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_DefaultButtonBase.h"

#include "CY_Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCY_DefaultButtonBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCY_DefaultButtonBase::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCY_DefaultButtonBase::SetData(const FLinearColor& BGColor, const FString& _ButtonText) const
{
	if(CPP_BGImage)
	{
		CPP_BGImage->SetColorAndOpacity(BGColor);
	}

	SetButtonText(_ButtonText);
}

void UCY_DefaultButtonBase::SetButtonText(const FString& _ButtonText) const
{
	if(CPP_ButtonText)
	{
		CPP_ButtonText->SetText(FText::FromString(_ButtonText));
	}
}

void UCY_DefaultButtonBase::SetOnClickButton(const UCommonButtonBase::FCommonButtonEvent& CommonButtonEvent) const
{
	if(CPP_DefaultButton)
	{
		CPP_DefaultButton->SetOnClickedDelegate(CommonButtonEvent);
	}
}
