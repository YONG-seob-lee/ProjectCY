// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_WorldMapIcon.h"
#include "CY_Button.h"
#include "Components/Image.h"

void UCY_Widget_WorldMapIcon::InitStaticPosition(TObjectPtr<UTexture2D> IconTexture, const FVector& _StaticPosition) const
{
	if(IconTexture != nullptr)
	{
		CPP_IconImage->SetBrushFromTexture(IconTexture, true);
	}
	
	if(_StaticPosition != FVector::ZeroVector)
	{
		CPP_Button->SetCustomVector(_StaticPosition);
	}
}

void UCY_Widget_WorldMapIcon::SetIconTexture(TObjectPtr<UTexture2D> Texture) const
{
	CPP_IconImage->SetBrushFromTexture(Texture);
}
