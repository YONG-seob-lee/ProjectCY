// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_UnitBase.h"

#include "CY_TableManager.h"
#include "CY_UnitManager.h"
#include "Resource_Unit.h"
#include "AnimInstance/CY_AnimInstance.h"
#include "Character/CY_CharacterBase.h"

void UCY_UnitBase::Initialize()
{
}

void UCY_UnitBase::Finalize()
{
	DestroyUnit();
}

bool UCY_UnitBase::CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot)
{
	ResourceUnitTableId = UnitTableId;
	ResourceUnitData = gTableMng.GetTableRowData<FResource_Unit>(ECY_TableDataType::Resource_Unit, ResourceUnitTableId);
	if(ResourceUnitData == nullptr)
	{
		return false;
	}

	const FString BPPath = gTableMng.GetPath(ECY_TableDataType::BasePath_BP_File, ResourceUnitData->Base_Path, true);
	if(const TObjectPtr<ACY_CharacterBase> NewCharacter = gUnitMng.CreateCharacter(BPPath, FPaths::GetCleanFilename(BPPath), Pos, Rot))
	{
		CharacterBase = NewCharacter;
	}
	
	return true;
}

void UCY_UnitBase::DestroyUnit()
{
}

void UCY_UnitBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine) const
{
	if(IsValidCharacterActor())
	{
		CharacterBase->SetLodScaleValues(CullDistanceScale, OutLineCullDistanceScale, bVisibleOutLine);
	}
}

float UCY_UnitBase::GetMovingSpeed() const
{
	if(const TObjectPtr<UCY_AnimInstance> AnimInstance = GetAnimInstance())
	{
		return AnimInstance->GetMovingSpeed();
	}

	return 0.f;
}

TObjectPtr<UCY_AnimInstance> UCY_UnitBase::GetAnimInstance() const
{
	if(const TObjectPtr<ACY_CharacterBase> Character = GetCharacterBase())
	{
		return Character->GetAnimInstance();
	}

	return nullptr; 
}
