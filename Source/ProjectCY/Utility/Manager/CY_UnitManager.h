// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Singleton.h"
#include "Engine/StreamableManager.h"
#include "UObject/Object.h"
#include "CY_UnitManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_UnitManager : public UObject, public UCY_Singleton<UCY_UnitManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	TObjectPtr<class UCY_UnitBase> CreateUnit(int32 UnitTableId, TSubclassOf<UCY_UnitBase> UnitType, const FVector& Position = FVector::ZeroVector, const FRotator& Rotator = FRotator::ZeroRotator);

	void DestroyUnit(CY_Handle UnitHandle);
	void DestroyAllUnit();

	FORCEINLINE FStreamableManager& GetAssetLoader() { return AssetLoader; }

	TObjectPtr<AActor> SpawnActor(UClass* Class, const FVector& Location, const FRotator& Rotation, const FString &LabelName, ESpawnActorCollisionHandlingMethod CollisionMathod, bool bNeedRootComponent);
	TObjectPtr<class ACY_CharacterBase> CreateCharacter(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot);

	TObjectPtr<UCY_UnitBase> GetUnit(CY_Handle UnitHandle);
	TObjectPtr<ACY_CharacterBase> GetCharacterBase(CY_Handle UnitHandle);
	CY_Handle GetIsValidBasePlayer();

private:
	CY_Handle MakeUnitHandle(const TObjectPtr<UCY_UnitBase> Unit) const;
	
	UPROPERTY()
	TMap<int32, TObjectPtr<UCY_UnitBase>> Units;

	float LodScale = 1.f;
	bool bOutLineModeOn = true;

	FStreamableManager AssetLoader;
#define gUnitMng (*UCY_UnitManager::GetInstance())
};
