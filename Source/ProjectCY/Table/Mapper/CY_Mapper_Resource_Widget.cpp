// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Mapper_Resource_Widget.h"

void UCY_Mapper_Resource_Widget::Initialize(TObjectPtr<UCY_TableManager> Mng)
{
	TMap<int32, TObjectPtr<FResource_Widget>> PrimitiveResourceWidget;
	PrimitiveResourceWidget.Empty();
	
	BuildTable(Mng, ECY_TableDataType::Resource_Widget, PrimitiveResourceWidget);

	for(const auto& ResourceWidgetData : PrimitiveResourceWidget)
	{
		ResourceWidgetDatas.Emplace(ResourceWidgetData.Value->TypeName, ResourceWidgetData.Value);
	}
}

void UCY_Mapper_Resource_Widget::Finalize()
{
	ResourceWidgetDatas.Empty();
	
	Super::Finalize();
}

TObjectPtr<FResource_Widget> UCY_Mapper_Resource_Widget::GetResourceWidgetData(const FName& TypeName)
{
	if(const TObjectPtr<FResource_Widget>* pResourceWidgetData = ResourceWidgetDatas.Find(TypeName))
	{
		return *pResourceWidgetData;
	}

	return nullptr;
}
