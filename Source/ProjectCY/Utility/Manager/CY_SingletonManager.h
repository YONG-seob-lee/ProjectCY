// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CY_SingletonManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_SingletonManager : public UObject
{
	GENERATED_BODY()
public:
	static TObjectPtr<UCY_SingletonManager> CreateInstance();
	static void DestroyInstance();
	static TObjectPtr<UCY_SingletonManager> GetInstance() { return Instance; }


	void BuiltInInitializeSingletons();
	void TickSingletons(float DeltaTime);

	void RemoveSingletons();
	
	void FinalizeSingletons();
	
protected:
	static TObjectPtr<UCY_SingletonManager> Instance;

private:

	void RegisterSingletons();
	void RegisterSingletonsForTick();


	bool bIsBuiltInInitialized = false;
	bool bInitialized = false;
	TArray<TObjectPtr<class ISingleton>> Singletons;
	TArray<TObjectPtr<class ISingleton>> SingletonsForTick;
};
