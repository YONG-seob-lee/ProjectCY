// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_TableManager.h"
#include "CY_StateMachine.h"
#include "CY_Utility.h"
#include "Engine/DataTable.h"
#include "CY_TableDefine.h"
#include "CY_TableMapper.h"
#include "CY_Mapper_PalCharacter.h"
#include "CY_Define.h"

UCY_TableManager::UCY_TableManager()
{
}

UCY_TableManager::~UCY_TableManager()
{
}

void UCY_TableManager::Initialize()
{
	MakeTableStructData();
}

void UCY_TableManager::Finalize()
{
	for (const auto& TableMapper : TableMappers)
	{
		TableMapper.Value.~FCY_TableMapperData();
	}
}

void UCY_TableManager::Tick(float DeltaTime)
{

}

void UCY_TableManager::GetRowDataMap(ECY_TableDataType TableType, TMap<FName, uint8*>& OutMapper)
{
	const FString& Name = CY_Utility::ConvertEnumToString<ECY_TableDataType>("ETableDataType", TableType);

	TObjectPtr<FCY_TableMapperData> pTable = TableMappers.Find(TableType);
	if (pTable == nullptr)
	{
		return;
	}

	TObjectPtr<UDataTable> TableData = pTable->GetTableData();
	if (TableData == nullptr)
	{
		return;
	}

	OutMapper = TableData->GetRowMap();
}

TObjectPtr<FCY_TableMapperData> UCY_TableManager::GetTableMapperData(ECY_TableDataType TableType)
{
	TObjectPtr<FCY_TableMapperData> TableMapper = TableMappers.Find(TableType);
	if (TableMapper == nullptr)
	{
		const FString& TableName = CY_Utility::ConvertEnumToString<ECY_TableDataType>("ECY_TableDataType", TableType);
		CY_LOG(TEXT("Wrong Table Type. Please Check (%s) Table Type"), *TableName);
		return nullptr;
	}

	return TableMapper;
}

FString UCY_TableManager::GetPath(ECY_TableDataType TableType)
{
	TObjectPtr<FCY_TableMapperData> TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return FString();
	}

	return TableMapper->GetTablePath();
}

const TObjectPtr<UDataTable> UCY_TableManager::GetTableData(ECY_TableDataType TableType)
{
	TObjectPtr<FCY_TableMapperData> TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return nullptr;
	}

	return TableMapper->GetTableData();
}

const TObjectPtr<class UCY_TableMapper> UCY_TableManager::GetTableMapper(ECY_TableDataType TableType)
{
	TObjectPtr<FCY_TableMapperData> TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return nullptr;
	}

	return TableMapper->GetTableMapper();
}

void UCY_TableManager::ResetData()
{
	TableMappers.Empty();
}

void UCY_TableManager::CreateTableData(ECY_TableDataType TableType, TSubclassOf<UCY_TableMapper> MapperType, const FString& Path)
{
	const FString& TableName = CY_Utility::ConvertEnumToString<ECY_TableDataType>("ECY_TableDataType", TableType);

	if (TableMappers.Find(TableType))
	{
		return;
	}

	// 테이블 데이터 오브젝트 생성
	TObjectPtr<UDataTable> TableObject = CY_Utility::LoadTableObjectFromFile(Path, TableName, FCY_LoadResourceDelegate::CreateUObject(this, &UCY_TableManager::LoadComplate));
	if (TableObject == nullptr)
	{
		return;
	}

	// 매퍼 생성 및 초기화
	TObjectPtr<UCY_TableMapper> TableMapper = CY_NewObject<UCY_TableMapper>(this, MapperType);
	if (TableMapper == nullptr)
	{
		return;
	}
	TableMapper->Initialize(this);

	// 추가.
	TableMappers.Emplace(TableType, FCY_TableMapperData(Path, TableObject, TableMapper));
}

void UCY_TableManager::MakeTableStructData()
{
	ResetData();

	CreateTableData(ECY_TableDataType::Pal_Character, UCY_Mapper_PalCharacter::StaticClass(), "/Game/TableData/Pal_Character.Pal_Character");
}

void UCY_TableManager::LoadComplate(const FString& TableName, TObjectPtr<UDataTable> TableData)
{

}
