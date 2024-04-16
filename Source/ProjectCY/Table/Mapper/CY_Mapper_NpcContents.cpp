// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Mapper_NpcContents.h"

#include "Npc_Contents.h"

void UCY_Mapper_NpcContents::Initialize(TObjectPtr<UCY_TableManager> Mng)
{
	BuildTable(Mng, ECY_TableDataType::Npc_Contents, NpcContents);
}

void UCY_Mapper_NpcContents::Finalize()
{
	Super::Finalize();
}

void UCY_Mapper_NpcContents::GetNpcContentDatas(int32 UnitId, TMap<FString, int32>& ContentDatas)
{
	ContentDatas.Empty();
	
	for(const auto& NpcContent : NpcContents)
	{
		if(NpcContent.Value->UnitId == UnitId)
		{
			ContentDatas.Emplace(NpcContent.Value->ContentName, NpcContent.Value->ImageType);		
		}
	}
}
