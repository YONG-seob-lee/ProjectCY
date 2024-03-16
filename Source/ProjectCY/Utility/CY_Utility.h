// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CY_TableDefine.h"
#include "Engine/StreamableManager.h"
/**
 * 
 */

namespace CY_Utility
{
	// todo 용섭 : Enum 을 FString 으로 변환하는 메소드
	template<typename TEnum>
	FString ConvertEnumToString(const FString& EnumString, TEnum EnumType)
	{
		const UEnum* pEnum = FindObject<UEnum>(nullptr, *EnumString, true);
		if (!pEnum) {
			return FString("");
		}

		int32 Index = pEnum->GetIndexByValue(static_cast<int32>(EnumType));
		return pEnum->GetNameStringByIndex(Index);
	}

	TObjectPtr<UDataTable> LoadTableObjectFromFile(const FString& ResourcePath, const FString& TableName, FCY_LoadResourceDelegate Delegate);
	TObjectPtr<UObject> LoadObjectFromFile(const FString& ResourcePath, const FCY_LoadResourceDelegate& Delegate, const FString& SubName = TEXT("SubName"), int32 Index = 0, bool SubBool = false);
	
}
