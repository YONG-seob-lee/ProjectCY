// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BasicGameUtility.h"
#include "CY_GameInstance.h"
#include "CY_PlayerController.h"
#include "CY_UnitManager.h"
#include "CY_Utility.h"
#include "Kismet/GameplayStatics.h"
#include "Slate/SceneViewport.h"

TObjectPtr<UCY_BasicGameUtility> UCY_BasicGameUtility::ThisInstance = nullptr;

void UCY_BasicGameUtility::Initialize(TObjectPtr<UCY_GameInstance> _GameInstance)
{
	GameInstance = _GameInstance;
}

void UCY_BasicGameUtility::Finalize()
{
	GameInstance = nullptr;
}

void UCY_BasicGameUtility::ShowMessageOnScreen(const FString& Message, bool bNewerOnTop /* = true */, float ElapsedTime /* = 3.f */, FColor DisplayColor /* = FColor::Green */)
{
	GEngine->AddOnScreenDebugMessage(-1, ElapsedTime, DisplayColor, Message);
}

TObjectPtr<AActor> UCY_BasicGameUtility::SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent /* = true */, 
                                                             ESpawnActorCollisionHandlingMethod Method /* = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn */)
{
	UClass* BlueprintClass = StaticLoadClass(UObject::StaticClass(), nullptr, *BlueprintPath);
	if(IsValid(BlueprintClass) == false)
	{
		CY_CHECK(false);
		CY_LOG(TEXT("Blueprint Path or Name is not Correct. Please Check Blueprint Path"));
		return nullptr;
	}
	
	const TObjectPtr<UWorld> World = GetGameWorld();
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
		ResultActor->SetActorLabel(CY_Utility::GetBPNameFromFullPath(BlueprintPath));

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

TObjectPtr<UCY_UnitBase> UCY_BasicGameUtility::GetCurrentPlayerUnit()
{
	const TObjectPtr<ACY_PlayerController> PlayerController = Cast<ACY_PlayerController>(GetPlayerController());
	if(PlayerController == nullptr)
	{
		return nullptr;
	}
	
	return gUnitMng.GetUnit(PlayerController->GetUnitHandle());
}

TObjectPtr<UWorld> UCY_BasicGameUtility::GetGameWorld()
{
	return ThisInstance ? ThisInstance->GameInstance ? ThisInstance->GameInstance->GetWorld() : nullptr : nullptr;
}

TObjectPtr<UCY_GameInstance> UCY_BasicGameUtility::GetGameInstance()
{
	return ThisInstance->GameInstance == nullptr ? nullptr : ThisInstance->GameInstance;
}

TObjectPtr<APlayerController> UCY_BasicGameUtility::GetPlayerController()
{
	const TObjectPtr<UWorld> World = GetGameWorld();
	if(World == nullptr)
	{
		return nullptr;
	}

	const TObjectPtr<APlayerController> Controller = UGameplayStatics::GetPlayerController(World, 0);

	return Controller ? Controller : nullptr;
}

TObjectPtr<FSceneViewport> UCY_BasicGameUtility::GetGameViewport()
{
	if(GEngine && GEngine->GameViewport)
	{
		return GEngine->GameViewport->GetGameViewport();
	}

	return nullptr;
}

bool UCY_BasicGameUtility::HasGameInstance()
{
	return ThisInstance->GameInstance != nullptr;
}

void UCY_BasicGameUtility::AssignUnitHandle(CY_Handle _UnitHandle)
{
	if(const TObjectPtr<ACY_PlayerController> PlayerController = Cast<ACY_PlayerController>(GetPlayerController()))
	{
		PlayerController->SetUnitHandle(_UnitHandle);
	}
}

float UCY_BasicGameUtility::GetAspectRatio()
{
	return GetGameViewport()->GetDesiredAspectRatio();
}

void UCY_BasicGameUtility::FlushPressedKeys()
{
	if(GetGameWorld())
	{
		if(const TObjectPtr<APlayerController> PlayerController = GetPlayerController())
		{
			PlayerController->FlushPressedKeys();
		}
	}
}
