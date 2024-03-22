// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BasePlayer.h"

#include "CY_StateMachine.h"
#include "CY_UnitManager.h"
#include "Character/CY_CharacterBase.h"


void UCY_BasePlayer::Initialize()
{
	Super::Initialize();
}

void UCY_BasePlayer::Finalize()
{
	Super::Finalize();
}

bool UCY_BasePlayer::CreatePlayerStateMachine()
{
	if(UnitHandle == InvalidUnitHandle)
	{
		return false;
	}

	PlayerStateMachine = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	PlayerStateMachine->AddToRoot();
	PlayerStateMachine->Create();

	return true;
}

void UCY_BasePlayer::SetSelfPlayer(bool _bSelfPlayer)
{
	bSelfPlayer = _bSelfPlayer;
}

void UCY_BasePlayer::ChangePlayerState(ECY_UnitState UnitState) const
{
	if(PlayerStateMachine)
	{
		PlayerStateMachine->SetState(UnitState);
	}
}

void UCY_BasePlayer::SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const
{
	if(const TObjectPtr<ACY_CharacterBase> Character = GetCharacterActor())
	{
		Character->SetPositionAndRotator(Position, Rotator);
	}
}

void UCY_BasePlayer::SetActorEnableCollision(bool bUnitEnableCollision) const
{
	const TObjectPtr<ACY_CharacterBase> Character = GetCharacterActor();
	if (UnitHandle != InvalidUnitHandle && IsValid(Character))
	{
		Character->SetActorEnableCollision(bUnitEnableCollision);
	}
}

void UCY_BasePlayer::ClearComponentOverlaps() const
{
	const TObjectPtr<ACY_CharacterBase> Character = GetCharacterActor();
	if (UnitHandle != InvalidUnitHandle && IsValid(Character))
	{
		Character->ClearComponentOverlaps();
		Character->UpdateOverlaps();
	}
}
