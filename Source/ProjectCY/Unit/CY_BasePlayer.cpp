// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BasePlayer.h"

#include "Character/CY_CharacterBase.h"


void UCY_BasePlayer::Initialize()
{
	Super::Initialize();
}

void UCY_BasePlayer::Finalize()
{
	Super::Finalize();
}

void UCY_BasePlayer::SetSelfPlayer(bool _bSelfPlayer)
{
	bSelfPlayer = _bSelfPlayer;
}

void UCY_BasePlayer::SetActorEnableCollision(bool bUnitEnableCollision) const
{
	ACY_CharacterBase* Character = GetCharacterActor();
	if (UnitHandle != InvalidUnitHandle && IsValid(Character))
	{
		Character->SetActorEnableCollision(bUnitEnableCollision);
	}
}

void UCY_BasePlayer::ClearComponentOverlaps() const
{
	ACY_CharacterBase* Character = GetCharacterActor();
	if (UnitHandle != InvalidUnitHandle && IsValid(Character))
	{
		Character->ClearComponentOverlaps();
		Character->UpdateOverlaps();
	}
}
