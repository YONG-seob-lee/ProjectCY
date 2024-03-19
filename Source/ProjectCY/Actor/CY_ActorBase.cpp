// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_ActorBase.h"


// Sets default values
ACY_ActorBase::ACY_ActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACY_ActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACY_ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

