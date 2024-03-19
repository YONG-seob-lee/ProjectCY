// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Actor_TeleportPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"


ACY_Actor_TeleportPoint::ACY_Actor_TeleportPoint(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), TeleportPointId(0)
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACY_Actor_TeleportPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACY_Actor_TeleportPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACY_Actor_TeleportPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ACY_Actor_TeleportPoint::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
}

void ACY_Actor_TeleportPoint::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

