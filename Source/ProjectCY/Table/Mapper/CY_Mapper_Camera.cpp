// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Mapper_Camera.h"

#include "CY_Utility.h"

void UCY_Mapper_Camera::Initialize(TObjectPtr<UCY_TableManager> Mng)
{
	BuildTable(Mng, ECY_TableDataType::Camera, CameraDatas);
}

void UCY_Mapper_Camera::Finalize()
{
	CameraDatas.Empty();
}

void UCY_Mapper_Camera::GetCameraFromType(TArray<FString>& SubCameras, const FString& CameraType)
{
	SubCameras.Empty();

	for(const auto& CameraData : CameraDatas)
	{
		if(CameraData.Value->Camera_Type == CameraType)
		{
			SubCameras.Emplace(CameraData.Value->Camera_Sub_Type);
		}
	}
}
