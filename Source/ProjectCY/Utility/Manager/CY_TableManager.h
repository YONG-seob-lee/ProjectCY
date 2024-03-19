// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Singleton.h"
#include "CY_TableDefine.h"
#include "CY_TableManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_TableManager : public UObject, public UCY_Singleton<UCY_TableManager>
{
	GENERATED_BODY()

public:
	UCY_TableManager();
	~UCY_TableManager();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	virtual void GetRowDataMap(ECY_TableDataType TableType, TMap<FName, uint8*>& OutMapper);

	TObjectPtr<FCY_TableMapperData> GetTableMapperData(ECY_TableDataType TableType);
	FString GetPath(ECY_TableDataType TableType, int32 Key, bool bResourcePath);
	FString GetDirectory(int32 DirectoryTableId);
	
	TObjectPtr<UDataTable> GetTableData(ECY_TableDataType TableType);

	
	TObjectPtr<UCY_TableMapper> GetTableMapper(ECY_TableDataType TableType);

	template<typename FRowData>
	TObjectPtr<FRowData> GetTableRowData(ECY_TableDataType TableType, int32 Key)
	{
		const TObjectPtr<FCY_TableMapperData> TableMapper = GetTableMapperData(TableType);
		if (TableMapper == nullptr)
		{
			return nullptr;
		}

		const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData();
		const FName KeyName = FName(FString::FromInt(Key));
		const FString Context = TEXT("GENERAL");
	
		return TableData->FindRow<FRowData>(KeyName, Context);
	}
private:
	void ResetData();
	void CreateTableData(ECY_TableDataType TableType, const FString& Path, TSubclassOf<UCY_TableMapper> MapperType = nullptr);
	void MakeTableStructData();

	void LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData);

	TMap<ECY_TableDataType, FCY_TableMapperData> TableMappers;

#define gTableMng (*UCY_TableManager::GetInstance())
};
