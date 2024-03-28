// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SceneLogo.h"

#include "CY_WidgetManager.h"
#include "CY_Widget_Logo.h"

void UCY_SceneLogo::Begin()
{
	gWidgetMng.CY_CreateWidget(UCY_Widget_Logo::GetWidgetName());
}

void UCY_SceneLogo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UCY_SceneLogo::Exit()
{
	Super::Exit();
}
