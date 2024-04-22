// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_MainHud.h"

#include "CY_Widget_TopHud.h"

void UCY_Widget_MainHud::NativeConstruct()
{
	CPP_TopHudWidget->InitTopHudWidget();
}

void UCY_Widget_MainHud::NativeDestruct()
{
}
