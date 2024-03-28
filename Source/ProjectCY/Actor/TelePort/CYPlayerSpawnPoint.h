// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "CYPlayerSpawnPoint.generated.h"

UCLASS(BlueprintType)
class PROJECTCY_API ACYPlayerSpawnPoint : public APlayerStart
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACYPlayerSpawnPoint(const FObjectInitializer& ObjectInitializer);
};
