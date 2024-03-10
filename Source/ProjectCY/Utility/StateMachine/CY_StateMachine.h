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
	void UnregistStates();

	UPROPERTY()
	TMap<int8, TObjectPtr<class UCY_StateBase>> EntireState;
};
