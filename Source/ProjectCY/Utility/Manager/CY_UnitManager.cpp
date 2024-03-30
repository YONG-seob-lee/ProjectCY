// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_UnitManager.h"

#include "CY_BasePlayer.h"
#include "CY_BasicGameUtility.h"
#include "CY_UnitBase.h"
#include "CY_Utility.h"
#include "Resource_Unit.h"
#include "Character/CY_CharacterBase.h"

void UCY_UnitManager::Initialize()
{
}

void UCY_UnitManager::Finalize()
{
	DestroyAllUnit();
}

void UCY_UnitManager::Tick(float _DeltaTime)
{
	for(const auto& Unit : Units)
	{
		Unit.Value->Tick(_DeltaTime);
	}
}

TObjectPtr<UCY_UnitBase> UCY_UnitManager::CreateUnit(int32 UnitTableId, TSubclassOf<UCY_UnitBase> UnitType, const FVector& Position, const FRotator& Rotator)
{
	const TObjectPtr<UCY_UnitBase> Unit = CY_NewObject<UCY_UnitBase>(this, UnitType);
	Unit->AddToRoot();
	Unit->Initialize();
	
	if(Unit->CreateUnit(UnitTableId, Position, Rotator) == false)
	{
		return nullptr;
	}

	Unit->SetLodScaleValues(LodScale, LodScale, bOutLineModeOn);

	const CY_Handle NewUnitHandle = MakeUnitHandle(Unit);
	
	if(NewUnitHandle == InvalidUnitHandle)
	{
		return nullptr;
	}
	
	Units.Add(NewUnitHandle, Unit);
	
	return Unit;
}

void UCY_UnitManager::DestroyUnit(CY_Handle UnitHandle)
{
	if(Units.Find(UnitHandle) != nullptr)
	{
		Units[UnitHandle]->RemoveFromRoot();
		Units[UnitHandle]->Finalize();
		Units[UnitHandle]->MarkAsGarbage();
		Units[UnitHandle] = nullptr;
		Units.Remove(UnitHandle);
	}
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

TObjectPtr<ACY_CharacterBase> UCY_UnitManager::CreateCharacter(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot)
{
	const TObjectPtr<ACY_CharacterBase> NewCharacter = Cast<ACY_CharacterBase>(UCY_BasicGameUtility::SpawnBlueprintActor(BlueprintPath, Pos, Rot));
	if(IsValid(NewCharacter))
	{
		NewCharacter->Create(CY_Utility::GetBPNameFromFullPath(BlueprintPath));
		return NewCharacter;
	}

	return nullptr;	
}

TObjectPtr<UCY_UnitBase> UCY_UnitManager::GetUnit(CY_Handle UnitHandle)
{
	const TObjectPtr<UCY_UnitBase>* pUnit = Units.Find(UnitHandle);

	return pUnit ? *pUnit : nullptr;
}

CY_Handle UCY_UnitManager::GetUnitHandle(TObjectPtr<UCY_UnitBase> UnitBase) const
{
	const CY_Handle* UnitHandle = Units.FindKey(UnitBase);

	return UnitHandle ? *UnitHandle : InvalidUnitHandle;
}

TObjectPtr<ACY_CharacterBase> UCY_UnitManager::GetCharacterBase(CY_Handle UnitHandle)
{
	const TObjectPtr<UCY_UnitBase>* pUnit = Units.Find(UnitHandle);

	return pUnit ? (*pUnit)->GetCharacterBase() : nullptr;
}

CY_Handle UCY_UnitManager::GetIsValidBasePlayer()
{
	for(const auto& Unit : Units)
	{
		if(const TObjectPtr<UCY_BasePlayer> BasePlayer = Cast<UCY_BasePlayer>(Unit.Value))
		{
			return BasePlayer->GetUnitHandle();			
		}
	}

	return InvalidUnitHandle;
}

CY_Handle UCY_UnitManager::MakeUnitHandle(const TObjectPtr<UCY_UnitBase> Unit) const
{
	const int32 UnitNum = Units.Num();
	const int32 NextUnitIndex = UnitNum + 1;

	if(Units.Contains(NextUnitIndex) == false)
	{
		Unit->SetUnitHandle(NextUnitIndex);
		return NextUnitIndex;
	}

	return InvalidUnitHandle;
}
