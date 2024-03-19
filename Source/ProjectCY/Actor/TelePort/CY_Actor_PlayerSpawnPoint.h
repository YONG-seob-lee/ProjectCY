// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Actor_TeleportPoint.h"
#include "CY_Actor_PlayerSpawnPoint.generated.h"

UCLASS()
class PROJECTCY_API ACY_Actor_PlayerSpawnPoint : public ACY_Actor_TeleportPoint
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACY_Actor_PlayerSpawnPoint(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
