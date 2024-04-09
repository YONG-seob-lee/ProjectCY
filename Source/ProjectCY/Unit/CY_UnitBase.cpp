// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_UnitBase.h"

#include "CY_StateMachine.h"
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
	OnActorTickDelegate.RemoveAll(this);
}

void UCY_UnitBase::Tick(float DeltaTime)
{
	OnActorTickDelegate.Broadcast(this);

	if(ActionStateMachine)
	{
		ActionStateMachine->Tick(DeltaTime);
	}
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
	if(const TObjectPtr<ACY_CharacterBase> NewCharacter = gUnitMng.CreateCharacter(BPPath, Pos, Rot))
	{
		CharacterBase = NewCharacter;

		if(const TObjectPtr<UCY_AnimInstance> AnimInstance = GetAnimInstance())
		{
			AnimInstance->SetMoveSpeedInfo(ResourceUnitData->WalkSpeed, ResourceUnitData->RunSpeed);
			AnimInstance->InitializeAnimation();
		}
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

void UCY_UnitBase::SetUnitPosition(const FVector& NewSpawnUnitPosition) const
{
	if(CharacterBase == nullptr)
	{
		return;
	}

	CharacterBase->SetActorLocation(NewSpawnUnitPosition);
}

float UCY_UnitBase::GetMovingSpeed() const
{
	if(const TObjectPtr<UCY_AnimInstance> AnimInstance = GetAnimInstance())
	{
		return AnimInstance->GetMovingSpeed();
	}

	return 0.f;
}

bool UCY_UnitBase::CreateActionStateMachine()
{
	if(UnitHandle == InvalidUnitHandle)
	{
		return false;
	}

	if(CharacterBase == nullptr)
	{
		return false;
	}

	ActionStateMachine = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	ActionStateMachine->AddToRoot();
	ActionStateMachine->Create();

	return true;
}

void UCY_UnitBase::DestroyActionStateMachine()
{
	if(ActionStateMachine)
	{
		ActionStateMachine->Destroy();
		ActionStateMachine->RemoveFromRoot();
		ActionStateMachine = nullptr;
	}
}

void UCY_UnitBase::AddActionState(ECY_UnitActionState State, const FName& Name, TSubclassOf<UCY_StateBase> ClassType)
{
	if(ActionStateMachine == nullptr)
	{
		return;
	}

	ActionStateMachine->RegistState(static_cast<uint8>(State), Name, ClassType, this);
}

void UCY_UnitBase::ChangeActionState(ECY_UnitActionState ActionType) const
{
	if(ActionStateMachine == nullptr)
	{
		return;
	}
	
	ActionStateMachine->SetState(static_cast<uint8>(ActionType));
}

TObjectPtr<UCY_AnimInstance> UCY_UnitBase::GetAnimInstance() const
{
	if(const TObjectPtr<ACY_CharacterBase> Character = GetCharacterBase())
	{
		return Character->GetAnimInstance();
	}

	return nullptr; 
}
