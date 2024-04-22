// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Mapper_Hud_TopExpander.h"

#include "Hud_TopExpander.h"

void UCY_Mapper_Hud_TopExpander::Initialize(TObjectPtr<UCY_TableManager> Mng)
{
	TMap<int32, TObjectPtr<FHud_TopExpander>> _ExpanderDatas;
	BuildTable(Mng, ECY_TableDataType::Hud_TopExpander, _ExpanderDatas);

	TopExpanderDatas.Empty();
	
	for(const auto & ExpanderData : _ExpanderDatas)
	{
		TopExpanderDatas.Emplace(ExpanderData.Value->Expander_Type, ExpanderData.Value);
	}
}

void UCY_Mapper_Hud_TopExpander::Finalize()
{
	Super::Finalize();
}
