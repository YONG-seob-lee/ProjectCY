// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Camera_PalWorld.h"

#include "CY_BasicGameUtility.h"
#include "CY_CameraActor.h"
#include "CY_CameraManager.h"
#include "CY_PlayerController.h"
#include "CY_UnitBase.h"
#include "CY_UnitManager.h"
#include "Components/CapsuleComponent.h"

namespace CameraSubType
{
	const FString Main = TEXT("Main");
	const FString Back = TEXT("Back"); 
	const FString Drone_01 = TEXT("Drone_01");
	const FString Drone_02 = TEXT("Drone_02");
	const FString Drone_03 = TEXT("Drone_03");
}

UCY_Camera_PalWorld::UCY_Camera_PalWorld()
{
	CameraData = FCY_CameraData(80.f, 50.f, FRotator(0.f, 0.f, 0.f), FVector(-300.f, -300.f, 40.f));
}

UCY_Camera_PalWorld::~UCY_Camera_PalWorld()
{
}

void UCY_Camera_PalWorld::Initialize(uint8 Index, const FName& Name)
{
	Super::Initialize(Index, Name);
}

void UCY_Camera_PalWorld::Finalize()
{
	Super::Finalize();
}

void UCY_Camera_PalWorld::Begin()
{
	if(gCameraMng.HasCamera(ECY_GameCameraType::PalWorld) == false)
	{
		if(const TObjectPtr<UCY_GameInstance> GameInstance = UCY_BasicGameUtility::GetGameInstance())
		{
			const TSubclassOf<ACY_CameraActor> CameraActor = GameInstance->GetCameraActor();
			if(CameraActor != nullptr)
			{
				Cameras = gCameraMng.CreateCameraActor(CameraActor, ECY_GameCameraType::PalWorld);
			}
		}

		MainCamera = gCameraMng.ActiveCamera(ECY_GameCameraType::PalWorld, CameraSubType::Main);
		if(MainCamera != nullptr)
		{
			TArray<UActorComponent*> CapsuleComponents = MainCamera->GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("CameraCollision"));
			if(CapsuleComponents.Num() > 0)
			{
				CameraCapsuleComponent = Cast<UCapsuleComponent>(CapsuleComponents[0]);

				if(CameraCapsuleComponent.IsValid())
				{
					CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
				}
			}
		}

		const TObjectPtr<ACY_PlayerController> PlayerController = Cast<ACY_PlayerController>(UCY_BasicGameUtility::GetPlayerController());
		if(PlayerController == nullptr)
		{
			return;
		}
		
		if(const TObjectPtr<UCY_UnitBase> UnitBase = gUnitMng.GetUnit(PlayerController->GetUnitHandle()))
		{
			ActorTickEvent = UnitBase->OnActorTickDelegate.AddUObject(this, &UCY_Camera_PalWorld::ActorTickFunc);
		}
	}
	else
	{
		//if(BlendTime < Curren)
	}

	
}

void UCY_Camera_PalWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UCY_Camera_PalWorld::Exit()
{
	if(CameraCapsuleComponent.IsValid())
	{
		CameraCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	Cameras.Reset();

	const TObjectPtr<ACY_PlayerController> PlayerController = Cast<ACY_PlayerController>(UCY_BasicGameUtility::GetPlayerController());
	if(PlayerController != nullptr)
	{
		return;
	}
	
	if(const TObjectPtr<UCY_UnitBase> UnitBase = gUnitMng.GetUnit(PlayerController->GetUnitHandle()))
	{
		UnitBase->OnActorTickDelegate.Remove(ActorTickEvent);
	}

	PlayerController->ResetUnitHandle();
	ActorTickEvent.Reset();
}

void UCY_Camera_PalWorld::ActorTickFunc(float DeltaTime, TObjectPtr<UCY_UnitBase> Unit)
{
	if(Unit == nullptr)
	{
		return;
	}

	const TObjectPtr<ACY_CharacterBase> Character = Unit->GetCharacterBase();

	if(Character == nullptr)
	{
		return;
	}

	ComputeCameraData(Unit->GetCharacterLocation());
}

void UCY_Camera_PalWorld::ComputeCameraData(const FVector& UnitVector) const
{
	MainCamera->SetCameraAspectRatio(UCY_BasicGameUtility::GetAspectRatio());
	MainCamera->SetFieldOfView(CameraData.FieldOfView);
	MainCamera->SetSpringOffset(CameraData.TargetOffset);
	MainCamera->SetCameraDistance(CameraData.Distance);

	MainCamera->SetTargetPosition(UnitVector - CameraData.ComputeRotateVector, UnitVector);
}
