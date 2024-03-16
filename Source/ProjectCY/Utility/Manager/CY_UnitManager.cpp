// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_UnitManager.h"

#include "CY_UnitBase.h"

void UCY_UnitManager::Initialize()
{
	UCY_Singleton<UCY_UnitManager>::Initialize();
}

void UCY_UnitManager::Finalize()
{
	DestroyAllUnit();
}

void UCY_UnitManager::Tick(float _DeltaTime)
{
	UCY_Singleton<UCY_UnitManager>::Tick(_DeltaTime);
}

TObjectPtr<UCY_UnitBase> UCY_UnitManager::CreateUnit(int32 UnitTableId, TSubclassOf<UCY_UnitBase> UnitType, const FVector& Pos, const FRotator& Rot)
{
	const TObjectPtr<UCY_UnitBase> Unit = CY_NewObject<UCY_UnitBase>(this, UnitType);
	Unit->AddToRoot();

	Unit->Initialize();
	if(Unit->CreateUnit(UnitTableId, Pos, Rot) == false)
	{
		return nullptr;
	}

	if(Unit->GetUnitHandle() == InvalidUnitHandle)
	{
		return nullptr;
	}

	Unit->SetLodScaleValues(LodScale, LodScale, bOutLineModeOn);

	Units.Add(Unit->GetUnitHandle(), Unit);
	return Unit;
}

void UCY_UnitManager::DestroyUnit()
{
}

void UCY_UnitManager::DestroyAllUnit()
{
	for(auto& Unit : Units)
	{
		if(Unit.Value == nullptr)
		{
			continue;
		}

		Unit.Value->RemoveFromRoot();
		Unit.Value->Finalize();
		Unit.Value->MarkAsGarbage();
		Unit.Value = nullptr;
	}
}
