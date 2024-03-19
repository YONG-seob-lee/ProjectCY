// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
//#include "CY_TableDefine.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_TwoParams(FCY_LoadResourceDelegate, const FString&, TObjectPtr<UObject>);

UENUM()
enum class ECY_TableDataType : uint8
{
	Pal_Character = 0				UMETA(DisplayName = "Pal_Character"),
	Hero_Level						UMETA(DisplayName = "Hero_Level"),
	Widget_Resource					UMETA(DisplayName = "Widget_Resource"),

	BasePath_Directory				UMETA(DisplayName = "BasePath_Directory"),
	BasePath_BP_File				UMETA(DisplayName = "BasePath_BP_File"),
};

struct FCY_TableMapperData
{
public:
	FCY_TableMapperData(const FString& _TablePath, TObjectPtr<UDataTable> _TableData, TObjectPtr<class UCY_TableMapper> _TableMapper) 
							: TablePath(_TablePath), TableData(_TableData), TableMapper(_TableMapper) {}
	~FCY_TableMapperData() { TableData = nullptr; TableMapper = nullptr; }

	FORCEINLINE const FString& GetTablePath() { return TablePath; }
	FORCEINLINE TObjectPtr<UDataTable> GetTableData() const { return TableData; }
	FORCEINLINE TObjectPtr<class UCY_TableMapper> GetTableMapper() const { return TableMapper; }
private:
	FString TablePath;
	TObjectPtr<UDataTable> TableData;
	TObjectPtr<class UCY_TableMapper> TableMapper;
};

//UCLASS()
//class PROJECTCY_API UCY_TableDefine : public UObject
//{
//	GENERATED_BODY()
//	
//};
