// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Singleton.h"
#include "UObject/Object.h"
#include "CY_UnitManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_UnitManager : public UObject, public UCY_Singleton<UCY_UnitManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	TObjectPtr<class UCY_UnitBase> CreateUnit(int32 UnitTableId, TSubclassOf<UCY_UnitBase> UnitType, const FVector& Pos = FVector::ZeroVector, const FRotator& Rot = FRotator::ZeroRotator);

	void DestroyUnit();
	void DestroyAllUnit();

private:
	UPROPERTY()
	TMap<int32, TObjectPtr<UCY_UnitBase>> Units;

	float LodScale = 1.f;
	bool bOutLineModeOn = true;

#define gUnitMng (*UCY_UnitManager::GetInstance())
};
