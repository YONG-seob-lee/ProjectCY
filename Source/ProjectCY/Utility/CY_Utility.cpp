// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Utility.h"

#include "CY_BasicGameUtility.h"
#include "CY_GameInstance.h"
#include "CY_UnitManager.h"
#include "Kismet/KismetMathLibrary.h"

TObjectPtr<AActor> CY_Utility::SpawnActor(UClass* Class, const FVector& Location, const FRotator& Rotation, const FString& LabelName, ESpawnActorCollisionHandlingMethod CollisionMathod, bool bNeedRootComponent)
{
	const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld();

	if (World == nullptr || Class == nullptr)
	{
		return nullptr;
	}
	AActor* NewActor = nullptr;
	
	FActorSpawnParameters Params;
	Params.OverrideLevel = World->GetCurrentLevel();
	Params.SpawnCollisionHandlingOverride = CollisionMathod;
	NewActor = World->SpawnActor(Class, &Location, &Rotation, Params);
	if (NewActor)
	{
#if WITH_EDITOR
		if (LabelName.IsEmpty() == false)
			NewActor->SetActorLabel(LabelName);
#endif

		if ((bNeedRootComponent == true) && (NewActor->GetRootComponent() == nullptr))
		{
			USceneComponent* RootComponent = NewObject<USceneComponent>(NewActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;
#if WITH_EDITORONLY_DATA
			RootComponent->bVisualizeComponent = false;
#endif
			NewActor->SetRootComponent(RootComponent);
			NewActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return NewActor;
}

const TCHAR* CY_Utility::AttachPathAsName(FString AssetPath, FString AssetName)
{
	AssetPath.Append(AssetName);
	AssetPath.Append(TEXT("."));
	AssetPath.Append(AssetName);

	return *AssetPath;
}

FString CY_Utility::GetBPNameFromFullPath(const FString& FullPath)
{
	if(FullPath.IsEmpty())
	{
		return FString();
	}

	int32 LastPoint = 0;
	int32 LastSlash = 0;
	constexpr TCHAR Point = '.';
	constexpr TCHAR Slash = '/';
	FullPath.FindLastChar(Point, LastPoint);
	FullPath.FindLastChar(Slash, LastSlash);

	return FullPath.Mid(LastSlash + 1, LastPoint - LastSlash - 1);
}

FRotator CY_Utility::MakeRotatorFromForward(const FVector& ForwardVector)
{
	return UKismetMathLibrary::MakeRotFromX(ForwardVector);
}

TObjectPtr<UDataTable> CY_Utility::LoadTableObjectFromFile(const FString& ResourcePath, const FString& TableName, FCY_LoadResourceDelegate Delegate)
{
	const TObjectPtr<UDataTable> ResultObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ResourcePath, *ResourcePath, LOAD_None, nullptr));
	Delegate.ExecuteIfBound(TableName, ResultObject);
	return ResultObject;
}

TObjectPtr<UObject> CY_Utility::LoadObjectFromFile(const FString& ResourcePath, const FCY_LoadResourceDelegate& Delegate /* = nullptr */, const FString& SubName /* = TEXT("SubName") */, int32 Index /* = 0 */, bool SubBool /* = false */)
{
	const FSoftObjectPath Reference = ResourcePath;
	UObject* ResultObject = gUnitMng.GetAssetLoader().LoadSynchronous(Reference);
	Delegate.ExecuteIfBound(ResourcePath, ResultObject);
	return ResultObject;
}
