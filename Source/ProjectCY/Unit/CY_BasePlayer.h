// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Define.h"
#include "CY_UnitBase.h"
#include "CY_BasePlayer.generated.h"

UCLASS()
class PROJECTCY_API UCY_BasePlayer : public UCY_UnitBase
{
	GENERATED_BODY()

public:
	virtual void Initialize() override;
	virtual void Finalize() override;

	void SetSelfPlayer(bool _bSelfPlayer);

	FORCEINLINE CY_Handle GetUnitHandle() const { return UnitHandle; }
	FORCEINLINE TObjectPtr<class ACY_CharacterBase> GetCharacterActor() const { return CharacterActor.Get(); }

	void SetActorEnableCollision(bool bUnitEnableCollision) const;
	void ClearComponentOverlaps() const;

protected:

	bool bSelfPlayer = false;

private:
	CY_Handle UnitHandle = InvalidUnitHandle;
	TWeakObjectPtr<ACY_CharacterBase> CharacterActor = nullptr;
};
