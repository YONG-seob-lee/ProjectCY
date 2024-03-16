// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_CharacterBase.h"


// Sets default values
ACY_CharacterBase::ACY_CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACY_CharacterBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine)
{
	LodValues.CullDistanceScale = CullDistanceScale;
	LodValues.OutLineCullDistanceScale = OutLineCullDistanceScale;
	LodValues.bVisibleOutLine = bVisibleOutLine;
}

// Called when the game starts or when spawned
void ACY_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACY_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACY_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

