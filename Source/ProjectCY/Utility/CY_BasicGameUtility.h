// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Define.h"
#include "CY_GameInstance.h"
#include "Character/CY_CharacterBase.h"
#include "CY_BasicGameUtility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_BasicGameUtility : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(TObjectPtr<UCY_GameInstance> _GameInstance);
	void Finalize();
	
	static void ShowMessageOnScreen(const FString& Message, bool bNewerOnTop = true, float ElapsedTime = 3.f, FColor DisplayColor = FColor::Green);

	static TObjectPtr<AActor> SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent = true,
	                                              ESpawnActorCollisionHandlingMethod Method = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	static TObjectPtr<UWorld> GetGameWorld();
	static TObjectPtr<UCY_GameInstance> GetGameInstance();
	static TObjectPtr<APlayerController> GetPlayerController();
	static TObjectPtr<FSceneViewport> GetGameViewport();
	static bool HasGameInstance();

	static void AssignUnitHandle(CY_Handle _UnitHandle);

	static float GetAspectRatio();
	static void FlushPressedKeys();
private:
	static TObjectPtr<UCY_BasicGameUtility> ThisInstance;
	
	UPROPERTY()
	TObjectPtr<UCY_GameInstance> GameInstance = nullptr;



//Todo. 용섭 : 인스턴스 생성 및 제거용(게임 인스턴스 들기용)
	
public:
	static TObjectPtr<UCY_BasicGameUtility> MakeInstance()
	{
		if(ThisInstance == nullptr)
		{
			ThisInstance = CY_NewObject<UCY_BasicGameUtility>();
			ThisInstance->AddToRoot();
		}
		return ThisInstance;
	}
	static void RemoveInstance()
	{
		if(ThisInstance != nullptr)
		{
			ThisInstance->RemoveFromRoot();
			ThisInstance->ConditionalBeginDestroy();
			ThisInstance = nullptr;
		}
	}
	static bool HasInstance()
	{
		return ThisInstance != nullptr ? true : false;
	}
	static TObjectPtr<UCY_BasicGameUtility> GetInstance()
	{
		return ThisInstance == nullptr ? nullptr : ThisInstance;
	}
};
