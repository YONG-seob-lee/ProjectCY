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

	void RegistState(int8 _nIndex, const FName& _name, TSubclassOf<class UPV_StateBase> _SceneType, UObject* _pOuter = nullptr);
	void UnregistStates();
};
