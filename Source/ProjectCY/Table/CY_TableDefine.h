// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CY_TableDefine.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_TwoParams(FCY_LoadResourceDelegate, const FString&, TObjectPtr<UObject>);

UENUM()
enum class ECY_TableDataType : uint8
{
	Common = 0						UMETA(DisplayName = "Common"),
	Pal_Character					UMETA(DisplayName = "Pal_Character"),
	Hero_Level						UMETA(DisplayName = "Hero_Level"),
	Resource_Widget					UMETA(DisplayName = "Resource_Widget"),
	Resource_Unit					UMETA(DisplayName = "Resource_Unit"),

	BasePath_Directory				UMETA(DisplayName = "BasePath_Directory"),
	BasePath_BP_File				UMETA(DisplayName = "BasePath_BP_File"),
	BasePath_Level_File				UMETA(DisplayName = "BasePath_Level_File"),
	BasePath_Img_File				UMETA(DisplayName = "BasePath_Img_File"),

	Camera							UMETA(DisplayName = "Camera"),
	Npc								UMETA(DisplayName = "Npc"),
	Npc_Contents					UMETA(DisplayName = "Npc_Contents"),
};

namespace CommonContents
{
	const FString Loading_Minimum_Time = TEXT("Loading_Minimum_Time");
	const FString Initial_Login = TEXT("Initial_Login");
}

USTRUCT()
struct FCY_TableMapperData
{
	GENERATED_USTRUCT_BODY()
public:
	FCY_TableMapperData() {}
	
	FCY_TableMapperData(const FString& _TablePath, TObjectPtr<UDataTable> _TableData, TObjectPtr<class UCY_TableMapper> _TableMapper) 
							: TablePath(_TablePath), TableData(_TableData), TableMapper(_TableMapper) {}
	~FCY_TableMapperData() { TableData = nullptr; TableMapper = nullptr; }

	void Finalize();
	
	FORCEINLINE const FString& GetTablePath() { return TablePath; }
	FORCEINLINE TObjectPtr<UDataTable> GetTableData() const { return TableData; }
	FORCEINLINE TObjectPtr<UCY_TableMapper> GetTableMapper() const { return TableMapper; }
private:
	FString TablePath = FString();
	
	UPROPERTY()
	TObjectPtr<UDataTable> TableData = nullptr;
	UPROPERTY()
	TObjectPtr<UCY_TableMapper> TableMapper = nullptr;
};