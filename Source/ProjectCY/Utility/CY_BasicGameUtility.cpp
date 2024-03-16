// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BasicGameUtility.h"
#include "CY_GameInstance.h"

UWorld* UCY_BasicGameUtility::GetGameWorld()
{
	if (gInstancePtr == nullptr)
	{
		return nullptr;
	}

	return gInstance.GetWorld();
}
