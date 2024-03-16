// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CY_ActorBase.generated.h"

UCLASS()
class PROJECTCY_API ACY_ActorBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACY_ActorBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
