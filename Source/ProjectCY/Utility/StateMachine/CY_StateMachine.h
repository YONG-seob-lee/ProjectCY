// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CY_StateMachine.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_StateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	void Create();
	void Destroy();
	void Tick(float _fDeltaTime);

	void RegistState(int8 Index, const FName& Name, TSubclassOf<class UCY_StateBase> SceneType, UObject* Outer = nullptr);
	void UnRegistStates();

	TObjectPtr<UCY_StateBase> GetCurrentState();;

	void SetState(int32 Index, bool _bInstant = true);

	FORCEINLINE TObjectPtr<UCY_StateBase> GetState(int32 Index) const;
private:
	void SetState_Internal(uint8 Index);
	
	UPROPERTY()
	TMap<int8, TObjectPtr<UCY_StateBase>> EntireState;

	uint8 PreviousStateId = -1;
	uint8 CurrentStateId = -1;
	uint8 ChangeStateId = -1;
};
