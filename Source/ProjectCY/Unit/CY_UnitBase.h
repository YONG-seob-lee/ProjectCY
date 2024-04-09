// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Define.h"
#include "CY_UnitDefine.h"
#include "Character/CY_CharacterBase.h"
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
	virtual void Tick(float DeltaTime);
	
	virtual bool CreateUnit(int32 UnitTableId, const FVector& Pos = FVector::ZeroVector, const FRotator& Rot = FRotator::ZeroRotator);
	virtual void DestroyUnit();

	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine) const;
	void SetUnitPosition(const FVector& NewSpawnUnitPosition) const;
	
	FORCEINLINE void SetUnitHandle(CY_Handle _UnitHandle) { UnitHandle = _UnitHandle; }
	FORCEINLINE CY_Handle GetUnitHandle() const { return UnitHandle; }
	
	FORCEINLINE TObjectPtr<struct FResource_Unit> GetResourceUnitData() const { return ResourceUnitData; }

	TObjectPtr<UCY_AnimInstance> GetAnimInstance() const;
	
	FORCEINLINE TObjectPtr<ACY_CharacterBase> GetCharacterBase() const { return CharacterBase.Get(); }
	FORCEINLINE FVector GetCharacterLocation() const { return CharacterBase->GetCurrentLocation(); }

	float GetMovingSpeed() const;
	
	FCY_UnitActorTickDelegate OnActorTickDelegate;

	
protected:
	bool CreateActionStateMachine();
	void DestroyActionStateMachine();
	void AddActionState(ECY_UnitActionState State, const FName& Name, TSubclassOf<class UCY_StateBase> ClassType);

	virtual void ChangeActionState(ECY_UnitActionState ActionType) const;
	
	TWeakObjectPtr<ACY_CharacterBase> CharacterBase = nullptr;
private:
	FORCEINLINE bool IsValidCharacterActor() const { return CharacterBase.IsValid(); }

	CY_Handle UnitHandle = InvalidUnitHandle;
	
	int32 ResourceUnitTableId = INDEX_NONE;
	TObjectPtr<FResource_Unit> ResourceUnitData = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> ActionStateMachine = nullptr;
};
