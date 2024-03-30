// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera.h"
#include "CY_SceneDefine.h"
#include "CY_TableMapper.h"
#include "CY_Mapper_Camera.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Mapper_Camera : public UCY_TableMapper
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UCY_TableManager> Mng) override;
	virtual void Finalize() override;

	void GetCameraFromType(TArray<FString>& SubCameras, const FString& CameraType);
private:
	TMap<int32, TObjectPtr<FCamera>> CameraDatas;
};
