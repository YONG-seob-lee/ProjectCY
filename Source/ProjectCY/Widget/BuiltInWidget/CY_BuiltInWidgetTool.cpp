// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BuiltInWidgetTool.h"

#include "Input/CY_PreTouchProcessor.h"

void UCY_BuiltInWidgetTool::Initialize()
{
	PreTouchProcessor = MakeShareable(new FCY_PreTouchProcessor());
	FSlateApplication::Get().RegisterInputPreProcessor(PreTouchProcessor);
	PreTouchProcessor->Initialize();
}

void UCY_BuiltInWidgetTool::Finalize()
{
	PreTouchProcessor->Finalize();
	FSlateApplication::Get().UnregisterInputPreProcessor(PreTouchProcessor);
}