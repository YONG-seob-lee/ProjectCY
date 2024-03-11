// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Utility.h"

TObjectPtr<UDataTable> CY_Utility::LoadTableObjectFromFile(const FString& ResourcePath, const FString& TableName, FCY_LoadResourceDelegate Delegate)
{
	TObjectPtr<UDataTable> ResultObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ResourcePath, *ResourcePath, LOAD_None, nullptr));
	Delegate.ExecuteIfBound(TableName, ResultObject);
	return ResultObject;
}
