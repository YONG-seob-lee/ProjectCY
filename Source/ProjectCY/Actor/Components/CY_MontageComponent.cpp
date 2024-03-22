// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_MontageComponent.h"


// Sets default values for this component's properties
UCY_MontageComponent::UCY_MontageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCY_MontageComponent::SetAnimInstance(TObjectPtr<UAnimInstance> NewAnimInstance)
{
	if(AnimInstance == NewAnimInstance)
	{
		return;
	}

	ClearCurrentMontagePool();

	AnimInstance = NewAnimInstance;
}


// Called when the game starts
void UCY_MontageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCY_MontageComponent::ClearCurrentMontagePool()
{
	if(AnimInstance == nullptr)
	{
		return;
	}

	if(AnimInstance->IsAnyMontagePlaying())
	{
		AnimInstance->Montage_Stop(0.f);
	}

	CurrentMontage.Empty();
	CurrentMontageName.Empty();
	CurrentMontageSectionName.Empty();
}


// Called every frame
void UCY_MontageComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

