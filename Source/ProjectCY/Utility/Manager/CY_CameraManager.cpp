// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_CameraManager.h"

#include "CY_Mapper_Camera.h"
#include "CY_StateMachine.h"
#include "CY_UnitManager.h"
#include "CY_Utility.h"
#include "Camera/CY_CameraActor.h"
#include "Camera/CY_Camera_PalWorld.h"

void UCY_CameraManager::BuiltInInitialize()
{
	if(CameraState)
	{
		return;
	}
	
	CameraState = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	CameraState->Create();
	CameraState->AddToRoot();
}

void UCY_CameraManager::Initialize()
{
	UCY_Singleton<UCY_CameraManager>::Initialize();
}

void UCY_CameraManager::Finalize()
{
	ResetData();
}

void UCY_CameraManager::BuiltInFinalize()
{
	if(CameraState)
	{
		CameraState->Destroy();
		CameraState->RemoveFromRoot();
		CameraState = nullptr;
	}	
}

void UCY_CameraManager::Tick(float _DeltaTime)
{
	if(CameraState)
	{
		CameraState->Tick(_DeltaTime);
	}
}

void UCY_CameraManager::RegisterCameras()
{
	RegistCameraState(static_cast<uint8>(ECY_GameCameraType::PalWorld), TEXT("PalWorld"), UCY_Camera_PalWorld::StaticClass());
}

void UCY_CameraManager::ResetData()
{
	CameraActors.Empty();
}

void UCY_CameraManager::DestroyAllCameras()
{
	CameraActors.Empty();
}

void UCY_CameraManager::ChangeCamera(uint8 Index, bool bInstant /* = true */) const
{
	if(CameraState)
	{
		CameraState->SetState(Index, bInstant);
	}
}

bool UCY_CameraManager::HasCamera(ECY_GameCameraType CameraType) const
{
	const FString CameraKeyName = CY_Utility::ConvertEnumToString<ECY_GameCameraType>("ECY_GameCameraType", CameraType);
	
	return CameraActors.Contains(CameraKeyName);
}

TMap<FString, TObjectPtr<ACY_CameraActor>> UCY_CameraManager::CreateCameraActor(TSubclassOf<ACY_CameraActor> CameraActorType, ECY_GameCameraType _CameraType)
{
	const FString CameraType = CY_Utility::ConvertEnumToString<ECY_GameCameraType>("ECY_GameCameraType", _CameraType);

	const TObjectPtr<UCY_Mapper_Camera> CameraMapper = Cast<UCY_Mapper_Camera>(gTableMng.GetTableMapper(ECY_TableDataType::Camera));
	if(!CameraMapper)
	{
		CY_CHECK(false);
		return {};
	}

	TArray<FString> SubCameras;
	CameraMapper->GetCameraFromType(SubCameras, CameraType);

	for(const FString& SubCamera : SubCameras)
	{
		const TObjectPtr<ACY_CameraActor> CameraActor = Cast<ACY_CameraActor>(CY_Utility::SpawnActor(CameraActorType, FVector::ZeroVector, FRotator::ZeroRotator, CameraType, ESpawnActorCollisionHandlingMethod::AlwaysSpawn, true));
		if(CameraActor == nullptr)
		{
			return {};
		}
	
#if WITH_EDITOR
		CameraActor->SetActorLabel(CameraActor->GetName());
#endif

		AddCameraActor(CameraType, SubCamera, CameraActor);
	}

	if(TMap<FString, TObjectPtr<ACY_CameraActor>>* TargetCameraActors = CameraActors.Find(CameraType))
	{
		return *TargetCameraActors;
	}
	
	return {};
}

TObjectPtr<ACY_CameraActor> UCY_CameraManager::ActiveCamera(ECY_GameCameraType _CameraType, const FString& CameraSubType, float BlendTime)
{
	const FString CameraType = CY_Utility::ConvertEnumToString<ECY_GameCameraType>("ECY_GameCameraType", _CameraType);
	
	const TMap<FString, TObjectPtr<ACY_CameraActor>>* pCameraActors = CameraActors.Find(CameraType);
	if(pCameraActors == nullptr)
	{
		return nullptr;
	}

	const TMap<FString, TObjectPtr<ACY_CameraActor>> TargetCameraActors = *pCameraActors;
	if(TargetCameraActors.Num() <= 0)
	{
		return nullptr;
	}

	const TObjectPtr<ACY_CameraActor>* pCameraActor = TargetCameraActors.Find(CameraSubType);
	if(pCameraActor == nullptr)
	{
		return nullptr;
	}
	
	CurrentActiveCamera = {CameraType, CameraSubType};
	(*pCameraActor)->Active(BlendTime);

	return (*pCameraActor);
}

TObjectPtr<UCY_StateBase> UCY_CameraManager::GetCurrentState() const
{
	return CameraState ? CameraState->GetCurrentState() : nullptr;
}

void UCY_CameraManager::RegistCameraState(uint8 Index, const FName& Name, TSubclassOf<UCY_StateBase> SceneType)
{
	if(CameraState)
	{
		CameraState->RegistState(Index, Name, SceneType);
	}
}

void UCY_CameraManager::AddCameraActor(const FString& CameraType, const FString& CameraSubType, TObjectPtr<ACY_CameraActor> CameraActor)
{
	if(TMap<FString, TObjectPtr<ACY_CameraActor>>* TargetCameraActors = CameraActors.Find(CameraType))
	{
		TargetCameraActors->Emplace(CameraSubType, CameraActor);
	}
	else
	{
		TMap<FString, TObjectPtr<ACY_CameraActor>> NewCameraActors;
		NewCameraActors.Emplace(CameraSubType, CameraActor);
		CameraActors.Emplace(CameraType, NewCameraActors);
	}
}
