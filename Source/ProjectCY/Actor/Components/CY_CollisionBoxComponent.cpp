// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_CollisionBoxComponent.h"


UCY_CollisionBoxComponent::UCY_CollisionBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCY_CollisionBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCY_CollisionBoxComponent::BeginPlay()
{
	Super::BeginPlay();
}


