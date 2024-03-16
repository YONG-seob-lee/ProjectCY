// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_UnitBase.h"

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

	return true;
}

void UCY_UnitBase::DestroyUnit()
{
}

void UCY_UnitBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine)
{
	if(IsValidCharacterActor())
	{
		CharacterBase->SetLodScaleValues(CullDistanceScale, OutLineCullDistanceScale, bVisibleOutLine);
	}
}
