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
	virtual bool CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot) override;
	virtual void DestroyUnit() override;

	bool CreatePlayerStateMachine();
	
	void SetSelfPlayer(bool _bSelfPlayer);
	void ChangePlayerState(ECY_UnitState UnitState) const;
	void SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const;
	
	FORCEINLINE CY_Handle GetUnitHandle() const { return UnitHandle; }

	void SetActorEnableCollision(bool bUnitEnableCollision) const;
	void ClearComponentOverlaps() const;
	
	void SetMoveSpeed(float MoveSpeed);
protected:

	bool bSelfPlayer = false;

private:
	UPROPERTY()
	TObjectPtr<class UCY_StateMachine> PlayerStateMachine = nullptr;
	
	CY_Handle UnitHandle = InvalidUnitHandle;
};
