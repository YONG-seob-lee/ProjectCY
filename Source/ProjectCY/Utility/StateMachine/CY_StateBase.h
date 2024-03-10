// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CY_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_StateBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(uint8 Index, const FName& Name);
	virtual void Finalize();

	UFUNCTION()
	void OnBeginState();
	UFUNCTION()
	void OnTickState();
	UFUNCTION()
	void OnExitState();

	FORCEINLINE uint8 GetStateIndex() { return StateIndex; }
	FORCEINLINE FName GetStateName() { return StateName; }

	TObjectPtr<class UCY_StateMachine> GetStateMachine();

protected:
	virtual void Begin() {}
	virtual void Tick(float DeltaTime) {}
	virtual void Exit() {}

private:
	UPROPERTY()
	int32 StateIndex = -1;
	UPROPERTY()
	FName StateName = {};
};
