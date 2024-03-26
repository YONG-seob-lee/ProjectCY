// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_Title.h"

#include "CY_DefaultButton.h"

void UCY_Widget_Title::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	if(CPP_StartButton)
	{
		CPP_StartButton->SetButtonText(TEXT("Game Start"));
	}

	if(CPP_ExitButton)
	{
		CPP_ExitButton->SetButtonText(TEXT("Exit"));
	}
}
