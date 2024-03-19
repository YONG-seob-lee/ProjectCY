// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SceneTitle.h"

#include "CY_WidgetManager.h"
#include "CY_Widget_Title.h"

void UCY_SceneTitle::Begin()
{
	gWidgetMng.CY_CreateWidget(UCY_Widget_Title::GetWidgetName());
}

void UCY_SceneTitle::Tick(float DeltaTime)
{
}

void UCY_SceneTitle::Exit()
{
}
