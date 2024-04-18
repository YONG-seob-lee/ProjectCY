// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_ImageButton.h"
#include "CY_Button.h"

void UCY_ImageButton::SetOnClickExitButton(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	if(CPP_Button)
	{
		CPP_Button->SetOnClickedDelegate(Event);
	}
}
