// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Mapper_Common.h"

void UCY_Mapper_Common::Initialize(TObjectPtr<UCY_TableManager> Mng)
{
	TMap<int32, TObjectPtr<FCommon>> TempDatas;
	TempDatas.Empty();
	BuildTable(Mng, ECY_TableDataType::Common, TempDatas);

	for(const auto& TempData : TempDatas)
	{
		CommonDatas.Emplace(TempData.Value->Contents, TempData.Value);
	}
}

void UCY_Mapper_Common::Finalize()
{
	Super::Finalize();
}

int32 UCY_Mapper_Common::GetParam01(const FString& CommonContents)
{
	if(const TObjectPtr<FCommon>* CommonData = CommonDatas.Find(CommonContents))
	{
		return (*CommonData)->Param01;
	}
	return 0;
}

int32 UCY_Mapper_Common::GetParam02(const FString& CommonContents)
{
	if(const TObjectPtr<FCommon>* CommonData = CommonDatas.Find(CommonContents))
	{
		return (*CommonData)->Param02;
	}
	return 0;
}

float UCY_Mapper_Common::GetParam03(const FString& CommonContents)
{
	if(const TObjectPtr<FCommon>* CommonData = CommonDatas.Find(CommonContents))
	{
		return (*CommonData)->Param03;
	}
	return 0;
}

float UCY_Mapper_Common::GetParam04(const FString& CommonContents)
{
	if(const TObjectPtr<FCommon>* CommonData = CommonDatas.Find(CommonContents))
	{
		return (*CommonData)->Param04;
	}
	return 0;
}
