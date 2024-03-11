// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

private:
	void ResetData();
	void CreateTableData(ECY_TableDataType TableType, TSubclassOf<UCY_TableMapper> MapperType, const FString& Path);
	void MakeTableStructAndPath();

	void LoadGameTable();
	void LoadComplate(const FString& TableName, TObjectPtr<UDataTable> TableData);

	TMap<ECY_TableDataType, FCY_TableMapperData> TableMappers;

#define gTableMng (TObjectPtr<UCY_TableManager::GetInseance()>)
};
