// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_DefaultButton.h"

#include "CY_Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCY_DefaultButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCY_DefaultButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCY_DefaultButton::SetData(const FLinearColor& BGColor, const FString& _ButtonText) const
{
	if(CPP_BGImage)
	{
		CPP_BGImage->SetColorAndOpacity(BGColor);
	}

	if(CPP_ButtonText)
	{
		CPP_ButtonText->SetText(FText::FromString(_ButtonText));
	}
}

void UCY_DefaultButton::SetOnClickButton(const UCommonButtonBase::FCommonButtonEvent& CommonButtonEvent) const
{
	if(CPP_DefaultButton)
	{
		CPP_DefaultButton->SetOnClickedDelegate(CommonButtonEvent);
	}
}
