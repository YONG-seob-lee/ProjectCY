// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BuiltInWidgetTool.h"

#include "CY_CameraActor.h"
#include "CY_CameraManager.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_Compass.h"
#include "CY_Widget_DialogScreenFader.h"
#include "CY_Widget_WorldMap.h"
#include "Input/CY_PreTouchProcessor.h"

void UCY_BuiltInWidgetTool::BuiltInitialize()
{
	DialogScreenFader = Cast<UCY_Widget_DialogScreenFader>(gWidgetMng.CreateWidgetNotManagingBySOP(UCY_Widget_DialogScreenFader::GetWidgetPath()));
	if(DialogScreenFader)
	{
		DialogScreenFader->FillDefaultAnimations();
		DialogScreenFader->AddToViewport(500);
		DialogScreenFader->SetVisibility(ESlateVisibility::Collapsed);
	}

	CompassWidget = Cast<UCY_Widget_Compass>(gWidgetMng.CreateWidgetNotManagingBySOP(UCY_Widget_Compass::GetWidgetPath()));
	if(CompassWidget)
	{
		CompassWidget->AddToViewport(100);
		CompassWidget->SetVisibility(ESlateVisibility::Collapsed);
		CompassWidget->Init();
	}
	
	PreTouchProcessor = MakeShareable(new FCY_PreTouchProcessor());
	FSlateApplication::Get().RegisterInputPreProcessor(PreTouchProcessor);
	PreTouchProcessor->Initialize();
}

void UCY_BuiltInWidgetTool::Initialize()
{
	WorldMapWidget = Cast<UCY_Widget_WorldMap>(gWidgetMng.CY_CreateWidget(UCY_Widget_WorldMap::GetWidgetName()));
	if(WorldMapWidget == nullptr)
	{
		CY_CHECK(false);
	}

	NpcInteractionWidget = Cast<UCY_Widget_NpcInteraction>(gWidgetMng.CY_CreateWidget(UCY_Widget_NpcInteraction::GetWidgetName()));
	if(NpcInteractionWidget == nullptr)
	{
		CY_CHECK(false);
	}
}

void UCY_BuiltInWidgetTool::Finalize()
{
	PreTouchProcessor->Finalize();
	FSlateApplication::Get().UnregisterInputPreProcessor(PreTouchProcessor);
}

void UCY_BuiltInWidgetTool::Tick(float DeltaTime)
{
	ProcessBuiltInCompass();
}

void UCY_BuiltInWidgetTool::ProcessBuiltInCompass() const
{
	if(const TObjectPtr<ACY_CameraActor> CameraActor = gCameraMng.GetCurrentActiveCameraActor())
	{
		if(CompassWidget)
		{
			CompassWidget->SetCompass(CameraActor->GetRotation().Yaw);
		}
	}	
}
