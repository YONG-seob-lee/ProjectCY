// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Actor_TeleportPoint.h"
#include "CY_Actor_BasePoint.generated.h"

UCLASS(BlueprintType)
class PROJECTCY_API ACY_Actor_BasePoint : public ACY_Actor_TeleportPoint
{
	GENERATED_BODY()

public:
	ACY_Actor_BasePoint(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<AActor> SpawnBasePoint();
};
