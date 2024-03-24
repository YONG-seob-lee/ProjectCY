// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Singleton.h"
#include "UObject/Object.h"
#include "CY_InputManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_InputManager : public UObject, public UCY_Singleton<UCY_InputManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	void CreateInputPawn();
	void DestroyInputPawn();

	FORCEINLINE FBindAllKeysDelegate& GetBindAllKeysDelegate() { return AllKeysDelegate; }

private:
	UPROPERTY()
	TObjectPtr<class ACY_Pawn_Input> InputPawn = nullptr;

	FBindAllKeysDelegate AllKeysDelegate;
#define gInputMng (*UCY_InputManager::GetInstance())
};
