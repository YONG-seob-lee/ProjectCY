// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BuiltInWidgetTool.h"

#include "CY_WidgetManager.h"
#include "CY_Widget_DialogScreenFader.h"
#include "Input/CY_PreTouchProcessor.h"

void UCY_BuiltInWidgetTool::Initialize()
{
	DialogScreenFader = Cast<UCY_Widget_DialogScreenFader>(gWidgetMng.CreateWidgetNotManagingBySOP(UCY_Widget_DialogScreenFader::GetWidgetPath()));
	if(DialogScreenFader)
	{
		DialogScreenFader->FillDefaultAnimations();
		DialogScreenFader->AddToViewport(500);
		DialogScreenFader->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	PreTouchProcessor = MakeShareable(new FCY_PreTouchProcessor());
	FSlateApplication::Get().RegisterInputPreProcessor(PreTouchProcessor);
	PreTouchProcessor->Initialize();
}

void UCY_BuiltInWidgetTool::Finalize()
{
	PreTouchProcessor->Finalize();
	FSlateApplication::Get().UnregisterInputPreProcessor(PreTouchProcessor);
}