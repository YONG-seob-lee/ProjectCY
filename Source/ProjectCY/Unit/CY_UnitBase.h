// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_UnitDefine.h"
#include "UObject/Object.h"
#include "CY_UnitBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_UnitBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize();
	virtual void Finalize();
	
	virtual bool CreateUnit(int32 UnitTableId, const FVector& Pos = FVector::ZeroVector, const FRotator& Rot = FRotator::ZeroRotator);
	virtual void DestroyUnit();

	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine);
	FORCEINLINE CY_UnitHandle GetUnitHandle() const { return UnitHandle; }

protected:
	TWeakObjectPtr<class ACY_CharacterBase> CharacterBase = nullptr;
private:
	FORCEINLINE bool IsValidCharacterActor() const { return CharacterBase.IsValid(); }
	CY_UnitHandle UnitHandle = InvalidUnitHandle;
};
