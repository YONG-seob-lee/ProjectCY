// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Define.h"
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

	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine) const;

	FORCEINLINE void SetUnitHandle(CY_Handle _UnitHandle) { UnitHandle = _UnitHandle; }
	FORCEINLINE CY_Handle GetUnitHandle() const { return UnitHandle; }
	
	FORCEINLINE TObjectPtr<struct FResource_Unit> GetResourceUnitData() const { return ResourceUnitData; }
	

	TObjectPtr<class UCY_AnimInstance> GetAnimInstance() const;
	FORCEINLINE TObjectPtr<class ACY_CharacterBase> GetCharacterBase() const { return CharacterBase.Get(); }
	
	float GetMovingSpeed() const;
protected:
	TWeakObjectPtr<ACY_CharacterBase> CharacterBase = nullptr;
private:
	FORCEINLINE bool IsValidCharacterActor() const { return CharacterBase.IsValid(); }

	int32 ResourceUnitTableId = INDEX_NONE;
	TObjectPtr<FResource_Unit> ResourceUnitData = nullptr;
	CY_Handle UnitHandle = InvalidUnitHandle;
};
