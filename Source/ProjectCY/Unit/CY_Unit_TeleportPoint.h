// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_UnitBase.h"
#include "Character/CY_CharacterBase.h"
#include "CY_Unit_TeleportPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Unit_TeleportPoint : public UCY_UnitBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	virtual bool CreateUnit(int32 UnitId, const FVector& Position = FVector::ZeroVector, const FRotator& Rotator = FRotator::ZeroRotator) override;
	virtual void DestroyUnit() override;
	
private:
	void BindCollisionComponent_Interaction(const float SphereRadius);
	
	UFUNCTION()
	void OnNpcInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnNpcInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	TObjectPtr<struct FNpc> NpcData = nullptr;
	FString NpcRoleType = FString();

	UPROPERTY()
	TObjectPtr<USphereComponent> Collision_Interaction = nullptr;
	
	TWeakObjectPtr<ACY_CharacterBase> CharacterBase = nullptr;
};
