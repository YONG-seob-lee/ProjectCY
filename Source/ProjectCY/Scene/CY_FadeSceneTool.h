// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_SceneDefine.h"
#include "UObject/Object.h"
#include "CY_FadeSceneTool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_FadeSceneTool : public UObject
{
	GENERATED_BODY()
public:
	void Request(class UCY_FadeCommand* Command);

	void Tick(float DeltaTime);
	
private:
	void StartFadeIn();
	void StartFadeOut();

	void PlayFadeAnimation(ECY_FadeStyle FadeType, bool bFadeIn, bool bDirectFadeIn);
	void OnWidgetFadeInFinished();
	void OnWidgetFadeOutFinished();
	
	ECY_FadeStep CurrentStep = ECY_FadeStep::Ready;
	bool bLoadStart = false;
	bool bLoadComplete = false;
	float LoadElapsedTime = 0.f;
	
	UPROPERTY()
	TArray<TObjectPtr<UCY_FadeCommand>> Commands;
	UPROPERTY()
	TObjectPtr<UCY_FadeCommand> FadeWidgetCommand = nullptr;
};
