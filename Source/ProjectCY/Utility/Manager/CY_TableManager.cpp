// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_TableManager.h"

#include "BasePath_BP_File.h"
#include "BasePath_Directory.h"
#include "BasePath_Img_File.h"
#include "BasePath_Level_File.h"
#include "CY_Utility.h"
#include "Engine/DataTable.h"
#include "CY_TableDefine.h"
#include "CY_TableMapper.h"
#include "CY_Mapper_PalCharacter.h"
#include "CY_Define.h"
#include "CY_Mapper_Camera.h"
#include "CY_Mapper_Common.h"
#include "CY_Mapper_Hud_TopExpander.h"
#include "CY_Mapper_NpcContents.h"
#include "CY_Mapper_Resource_Unit.h"
#include "CY_Mapper_Resource_Widget.h"
#include "CY_SceneDefine.h"

UCY_TableManager::UCY_TableManager()
{
}

UCY_TableManager::~UCY_TableManager()
{
}

void UCY_TableManager::Initialize()
{
	if(bInitialize)
	{
		return;
	}
	MakeTableStructData();

	bInitialize = true;
}

void UCY_TableManager::Finalize()
{
	for (auto& TableMapper : TableMappers)
	{
		TableMapper.Value.Finalize();
	}

	TableMappers.Empty();
}

void UCY_TableManager::Tick(float DeltaTime)
{

}

void UCY_TableManager::GetRowDataMap(ECY_TableDataType TableType, TMap<FName, uint8*>& OutMapper)
{
	const FString& Name = CY_Utility::ConvertEnumToString<ECY_TableDataType>("ECY_TableDataType", TableType);

	const TObjectPtr<FCY_TableMapperData> TableMapper = TableMappers.Find(TableType);
	if (TableMapper == nullptr)
	{
		return;
	}

	const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData();
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

FString UCY_TableManager::GetPath(ECY_TableDataType TableType, int32 Key, bool bResourcePath /* = false */)
{
	switch(TableType)
	{
	case ECY_TableDataType::BasePath_BP_File:
		{
			const TObjectPtr<FBasePath_BP_File> RowData = GetTableRowData<FBasePath_BP_File>(TableType, Key);
			
			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->BP_File_Name.ToString() + '.' + RowData->BP_File_Name.ToString() + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->BP_File_Name.ToString()});
		}
		break;
	case ECY_TableDataType::BasePath_Level_File:
		{
			const int32 TotalKeyIndex = GetTableRowNum(TableType) + 1;

			for(int32 i = 1 ; i != TotalKeyIndex ; i++)
			{
				if(const TObjectPtr<FBasePath_Level_File> RowData = GetTableRowData<FBasePath_Level_File>(TableType, i))
				{
					const FString TableDataType = CY_Utility::ConvertEnumToString<ECY_GameSceneType>("ECY_GameSceneType", static_cast<ECY_GameSceneType>(Key));
					if(RowData->Level_File_Name.ToString() == TableDataType)
					{
						return GetDirectory(RowData->Directory_Table_Id) + RowData->Level_File_Name.ToString();
					}
				}
			}
		}
		break;
	case ECY_TableDataType::BasePath_Img_File:
		{
			const TObjectPtr<FBasePath_Img_File> RowData = GetTableRowData<FBasePath_Img_File>(TableType, Key);

			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->Img_File_Name + '.' + RowData->Img_File_Name + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->Img_File_Name});
		}
		break;
	default:
		return FString();
	}

	return FString();
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
		// 추가.
		TableMappers.Emplace(TableType, FCY_TableMapperData(Path, TableObject, TableMapper));
		
		TableMapper->Initialize(this);
	}
	else
	{
		TableMappers.Emplace(TableType, FCY_TableMapperData(Path, TableObject, nullptr));
	}
}

void UCY_TableManager::MakeTableStructData()
{
	ResetData();
	CreateTableData(ECY_TableDataType::Common, "/Game/TableData/Common.Common", UCY_Mapper_Common::StaticClass());
	CreateTableData(ECY_TableDataType::BasePath_Directory, "/Game/TableData/BasePath_Directory.BasePath_Directory");
	CreateTableData(ECY_TableDataType::BasePath_BP_File, "/Game/TableData/BasePath_BP_File.BasePath_BP_File");
	CreateTableData(ECY_TableDataType::BasePath_Level_File, "/Game/TableData/BasePath_Level_File.BasePath_Level_File");
	CreateTableData(ECY_TableDataType::BasePath_Img_File, "/Game/TableData/BasePath_Img_File.BasePath_Img_File");

	CreateTableData(ECY_TableDataType::Resource_Widget, "/Game/TableData/Resource_Widget.Resource_Widget", UCY_Mapper_Resource_Widget::StaticClass());
	CreateTableData(ECY_TableDataType::Resource_Unit, "/Game/TableData/Resource_Unit.Resource_Unit", UCY_Mapper_Resource_Unit::StaticClass());
	
	CreateTableData(ECY_TableDataType::Camera, "/Game/TableData/Camera.Camera", UCY_Mapper_Camera::StaticClass());
	CreateTableData(ECY_TableDataType::Pal_Character, "/Game/TableData/Pal_Character.Pal_Character", UCY_Mapper_PalCharacter::StaticClass());
	CreateTableData(ECY_TableDataType::Npc, "/Game/TableData/Npc.Npc");
	CreateTableData(ECY_TableDataType::Npc_Contents, "/Game/TableData/Npc_Contents.Npc_Contents", UCY_Mapper_NpcContents::StaticClass());
	CreateTableData(ECY_TableDataType::Hud_TopExpander, "/Game/TableData/Hud_TopExpander.Hud_TopExpander", UCY_Mapper_Hud_TopExpander::StaticClass());
}

void UCY_TableManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData)
{
	
}
