// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_DefaultButton.h"

#include "CY_Button.h"

void UCY_DefaultButton::NativeConstruct()
{
}

void UCY_DefaultButton::NativeDestruct()
{
}

void UCY_DefaultButton::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UCY_DefaultButton::SetButtonText(const FString& ButtonText) const
{
	if(CPP_ButtonBase)
	{
		CPP_ButtonBase->SetText(ButtonText);
		
	}
}
