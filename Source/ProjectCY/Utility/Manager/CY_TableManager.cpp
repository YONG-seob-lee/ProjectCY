// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_TableManager.h"

#include "BasePath_BP_File.h"
#include "BasePath_Directory.h"
#include "CY_Utility.h"
#include "Engine/DataTable.h"
#include "CY_TableDefine.h"
#include "CY_TableMapper.h"
#include "CY_Mapper_PalCharacter.h"
#include "CY_Define.h"
#include "CY_Mapper_Resource_Widget.h"

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
	const FString& Name = CY_Utility::ConvertEnumToString<ECY_TableDataType>("ECY_TableDataType", TableType);

	const TObjectPtr<FCY_TableMapperData> pTable = TableMappers.Find(TableType);
	if (pTable == nullptr)
	{
		return;
	}

	const TObjectPtr<UDataTable> TableData = pTable->GetTableData();
	if (TableData == nullptr)
	{
		return;
	}

	OutMapper = TableData->GetRowMap();
}

TObjectPtr<FCY_TableMapperData> UCY_TableManager::GetTableMapperData(ECY_TableDataType TableType)
{
	const TObjectPtr<FCY_TableMapperData> TableMapper = TableMappers.Find(TableType);
	if (TableMapper == nullptr)
	{
		const FString& TableName = CY_Utility::ConvertEnumToString<ECY_TableDataType>("ECY_TableDataType", TableType);
		CY_LOG(TEXT("Wrong Table Type. Please Check (%s) Table Type"), *TableName);
		return nullptr;
	}

	return TableMapper;
}

FString UCY_TableManager::GetPath(ECY_TableDataType TableType, int32 Key, bool bResourcePath)
{
	switch(TableType)
	{
	case ECY_TableDataType::BasePath_BP_File:
		{
			const TObjectPtr<FBasePath_BP_File> RowData = GetTableRowData<FBasePath_BP_File>(TableType, Key);
			
			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->BP_File_Name.ToString()
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->BP_File_Name.ToString()});
		}
	default:
		return FString();
	}
	
}

FString UCY_TableManager::GetDirectory(int32 DirectoryTableId)
{
	if(DirectoryTableId == 0 || DirectoryTableId == INDEX_NONE)
	{
		return FString();
	}

	const TObjectPtr<FBasePath_Directory> RowData = GetTableRowData<FBasePath_Directory>(ECY_TableDataType::BasePath_Directory, DirectoryTableId);
	if(RowData == nullptr)
	{
		return FString();
	}

	FString ResultDirectory = RowData->Directory.StartsWith(TEXT("/Game/")) ? RowData->Directory : TEXT("/Game/") + RowData->Directory;

	return ResultDirectory[ResultDirectory.Len() - 1] != '/' ? ResultDirectory + "/" : ResultDirectory;
}

TObjectPtr<UDataTable> UCY_TableManager::GetTableData(ECY_TableDataType TableType)
{
	const TObjectPtr<FCY_TableMapperData> TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return nullptr;
	}

	return TableMapper->GetTableData();
}

TObjectPtr<class UCY_TableMapper> UCY_TableManager::GetTableMapper(ECY_TableDataType TableType)
{
	const TObjectPtr<FCY_TableMapperData> TableMapper = GetTableMapperData(TableType);
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

void UCY_TableManager::CreateTableData(ECY_TableDataType TableType, const FString& Path, TSubclassOf<UCY_TableMapper> MapperType /* = nullptr */)
{
	const FString& TableName = CY_Utility::ConvertEnumToString<ECY_TableDataType>("ECY_TableDataType", TableType);

	if (TableMappers.Find(TableType))
	{
		return;
	}

	// 테이블 데이터 오브젝트 생성
	const TObjectPtr<UDataTable> TableObject = CY_Utility::LoadTableObjectFromFile(Path, TableName, FCY_LoadResourceDelegate::CreateUObject(this, &UCY_TableManager::LoadComplete));
	if (TableObject == nullptr)
	{
		return;
	}

	// 매퍼 생성 및 초기화
	if(MapperType)
	{
		const TObjectPtr<UCY_TableMapper> TableMapper = CY_NewObject<UCY_TableMapper>(this, MapperType);
		if (TableMapper == nullptr)
		{
			return;
		}
		TableMapper->Initialize(this);

		// 추가.
		TableMappers.Emplace(TableType, FCY_TableMapperData(Path, TableObject, TableMapper));
	}
	else
	{
		TableMappers.Emplace(TableType, FCY_TableMapperData(Path, TableObject, nullptr));
	}
}

void UCY_TableManager::MakeTableStructData()
{
	ResetData();
	CreateTableData(ECY_TableDataType::BasePath_Directory, "/Game/TableData/BasePath_Directory.Directory");
	CreateTableData(ECY_TableDataType::BasePath_BP_File, "/Game/TableData/BasePath_BP_File.BasePath_BP_File");

	CreateTableData(ECY_TableDataType::Pal_Character, "/Game/TableData/Pal_Character.Pal_Character", UCY_Mapper_PalCharacter::StaticClass());
	CreateTableData(ECY_TableDataType::Widget_Resource, "/Game/TableData/Widget_Resource.Widget_Resource", UCY_Mapper_Resource_Widget::StaticClass());
}

void UCY_TableManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData)
{

}
