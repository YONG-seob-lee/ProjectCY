// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Utility.h"

#include "CY_GameInstance.h"
#include "CY_UnitManager.h"

const TCHAR* CY_Utility::AttachPathAsName(FString AssetPath, FString AssetName)
{
	AssetPath.Append(AssetName);
	AssetPath.Append(TEXT("."));
	AssetPath.Append(AssetName);

	return *AssetPath;
}

TObjectPtr<UDataTable> CY_Utility::LoadTableObjectFromFile(const FString& ResourcePath, const FString& TableName, FCY_LoadResourceDelegate Delegate)
{
	const TObjectPtr<UDataTable> ResultObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ResourcePath, *ResourcePath, LOAD_None, nullptr));
	Delegate.ExecuteIfBound(TableName, ResultObject);
	return ResultObject;
}

TObjectPtr<UObject> CY_Utility::LoadObjectFromFile(const FString& ResourcePath, const FCY_LoadResourceDelegate& Delegate /* = nullptr */, const FString& SubName /* = TEXT("SubName") */, int32 Index /* = 0 */, bool SubBool /* = false */)
{
	const FStringAssetReference Reference = ResourcePath;
	UObject* ResultObject = gUnitMng.GetAssetLoader().LoadSynchronous(Reference);
	Delegate.ExecuteIfBound(ResourcePath, ResultObject);
	return ResultObject;
}
