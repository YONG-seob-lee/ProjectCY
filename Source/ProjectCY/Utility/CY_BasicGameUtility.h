// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CY_BasicGameUtility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_BasicGameUtility : public UObject
{
	GENERATED_BODY()
	
public:
	UWorld* GetGameWorld();
};
