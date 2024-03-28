// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_UnitManager.h"

#include "CY_BasePlayer.h"
#include "CY_BasicGameUtility.h"
#include "CY_GameInstance.h"
#include "CY_UnitBase.h"
#include "CY_Utility.h"
#include "Character/CY_CharacterBase.h"

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

TObjectPtr<AActor> UCY_UnitManager::SpawnActor(UClass* Class, const FVector& Location, const FRotator& Rotation, const FString& LabelName, ESpawnActorCollisionHandlingMethod CollisionMathod, bool bNeedRootComponent)
{
	const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld();

	if (World == nullptr || Class == nullptr)
	{
		return nullptr;
	}
	AActor* NewActor = nullptr;
	
	FActorSpawnParameters Params;
	Params.OverrideLevel = World->GetCurrentLevel();
	Params.SpawnCollisionHandlingOverride = CollisionMathod;
	NewActor = World->SpawnActor(Class, &Location, &Rotation, Params);
	if (NewActor)
	{
#if WITH_EDITOR
		if (LabelName.IsEmpty() == false)
			NewActor->SetActorLabel(LabelName);
#endif

		if ((bNeedRootComponent == true) && (NewActor->GetRootComponent() == nullptr))
		{
			USceneComponent* RootComponent = NewObject<USceneComponent>(NewActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;
#if WITH_EDITORONLY_DATA
			RootComponent->bVisualizeComponent = false;
#endif
			NewActor->SetRootComponent(RootComponent);
			NewActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return NewActor;
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

	if(Units.Contains(UnitNum) == false)
	{
		constexpr int32 NextIndex = 1;
		Unit->SetUnitHandle(UnitNum + NextIndex);
		return UnitNum + NextIndex;
	}

	return InvalidUnitHandle;
}
