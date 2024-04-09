// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_UnitDefine.h"
#include "GameFramework/Actor.h"
#include "CY_ActorBase.generated.h"

UCLASS()
class PROJECTCY_API ACY_ActorBase : public AActor
{
	GENERATED_BODY()

public:
	ACY_ActorBase(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE ECY_InteractionType GetInteractionType() const { return ActorInteractionType; }
	
protected:
	virtual void BeginPlay() override;

	FORCEINLINE virtual void SetInteractionType(ECY_InteractionType Type) { ActorInteractionType = Type; }

public:
	virtual void Tick(float DeltaTime) override;

private:
	ECY_InteractionType ActorInteractionType = ECY_InteractionType::None;
};
