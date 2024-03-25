// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_TableDefine.h"

#include "CY_TableMapper.h"

void FCY_TableMapperData::Finalize()
{
	TablePath = nullptr;
	TableData = nullptr;
	
	if(IsValid(TableMapper))
	{
		TableMapper->Finalize();
		CY_DeleteObject(TableMapper);
	}
}
