// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BasicGameUtility.h"
#include "CY_GameInstance.h"

TObjectPtr<UCY_BasicGameUtility> UCY_BasicGameUtility::ThisInstance = nullptr;

void UCY_BasicGameUtility::Initialize(TObjectPtr<UCY_GameInstance> _GameInstance)
{
	GameInstance = _GameInstance;
}

void UCY_BasicGameUtility::Finalize()
{
	GameInstance = nullptr;
}

TObjectPtr<AActor> UCY_BasicGameUtility::SpawnBlueprintActor(const FString& BlueprintFileName, const FVector& Pos, const FRotator& Rot,
                                                             TSubclassOf<ACharacter> CharacterType /* = ACY_CharacterBase::StaticClass() */, bool bNeedRootComponent /* = true */, 
                                                             ESpawnActorCollisionHandlingMethod Method /* = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn */)
{
	const TObjectPtr<UClass> BlueprintClass = StaticLoadClass(CharacterType, nullptr, *BlueprintFileName);
	if(IsValid(BlueprintClass) == false)
	{
		return nullptr;
	}
	
	const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld();
		if(IsValid(World) == false)
		{
			return nullptr;	
		}
			
	FActorSpawnParameters Parameters;
	Parameters.OverrideLevel = World->GetCurrentLevel();
	Parameters.SpawnCollisionHandlingOverride = Method;
	const TObjectPtr<AActor> ResultActor = World->SpawnActor(BlueprintClass, &Pos, &Rot, Parameters);

	if(ResultActor)
	{
		ResultActor->SetActorLabel(BlueprintFileName);

		if(bNeedRootComponent && ResultActor->GetRootComponent() == nullptr)
		{
			const TObjectPtr<USceneComponent> RootComponent = NewObject<USceneComponent>(ResultActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;

			ResultActor->SetRootComponent(RootComponent);
			ResultActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return ResultActor != nullptr ? ResultActor : nullptr;
}

TObjectPtr<UWorld> UCY_BasicGameUtility::GetGameWorld()
{
	return ThisInstance ? ThisInstance->GameInstance ? ThisInstance->GameInstance->GetWorld() : nullptr : nullptr;
}

TObjectPtr<UCY_GameInstance> UCY_BasicGameUtility::GetGameInstance()
{
	return ThisInstance->GameInstance == nullptr ? nullptr : ThisInstance->GameInstance;
}

bool UCY_BasicGameUtility::HasGameInstance()
{
	return ThisInstance->GameInstance != nullptr;
}
