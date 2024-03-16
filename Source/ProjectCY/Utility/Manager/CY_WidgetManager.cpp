// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_WidgetManager.h"
#include "CY_StateMachine.h"
#include "CY_Define.h"
#include "CY_WidgetDefine.h"

UCY_WidgetManager::UCY_WidgetManager()
{
}

UCY_WidgetManager::~UCY_WidgetManager()
{
}

void UCY_WidgetManager::Initialize()
{
	WidgetMachine = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	WidgetMachine->AddToRoot();
	WidgetMachine->Create();
}

void UCY_WidgetManager::Finalize()
{
}

void UCY_WidgetManager::Tick(float DeltaTime)
{
	if (WidgetMachine)
	{
		WidgetMachine->Tick(DeltaTime);
	}
}

void UCY_WidgetManager::ClearExclusiveLayer()
{
	constexpr uint8 Top = static_cast<uint8>(ECY_ExclusiveGroup::TopMenu);
	constexpr uint8 Content = static_cast<uint8>(ECY_ExclusiveGroup::ContentMenu);

	if(ExclusiveLayers.IsValidIndex(Top))
	{
		ExclusiveLayers[Top] = nullptr;
	}
	if(ExclusiveLayers.IsValidIndex(Content))
	{
		ExclusiveLayers[Content] = nullptr;
	}
}
