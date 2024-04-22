// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_ImageButton.h"
#include "CY_Button.h"
#include "Components/Image.h"

void UCY_ImageButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if(Texture2D && CPP_Image)
	{
		CPP_Image->SetBrushFromTexture(Texture2D);
	}
}

void UCY_ImageButton::SetOnClickImageButton(const UCommonButtonBase::FCommonButtonEvent& Event) const
{
	if(CPP_Button)
	{
		CPP_Button->SetOnClickedDelegate(Event);
	}
}
