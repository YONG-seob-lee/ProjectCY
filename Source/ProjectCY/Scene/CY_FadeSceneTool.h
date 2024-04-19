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
	void Initialize();
	
	void RegistLevelPath(uint8 SceneId);
	
	void Request(class UCY_FadeCommand* Command);
	void FinishRequest();

	void Tick(float DeltaTime);
	FString GetLevelPath(ECY_GameSceneType SceneType);

private:
	void StartFadeOut();
	void StartFadeIn();

	void PlayFadeAnimation(ECY_FadeStyle FadeType, bool bFadeIn, bool bDirectFadeIn);
	void PlayDrone(bool bIsFadeOut = true);
	void OnWidgetFadeOutFinished();
	void OnWidgetFadeInFinished();

	void OnCameraFadeOutFinished();
	void OnCameraFadeInFinished();
	
	ECY_FadeStep CurrentStep = ECY_FadeStep::Ready;
	bool bLoadStart = false;
	bool bLoadComplete = false;

	float LoadingMinimumTime = 0.f;
	float LoadElapsedTime = 0.f;

	UPROPERTY()
	TMap<uint8, FString> LevelsPath;
	UPROPERTY()
	TArray<TObjectPtr<UCY_FadeCommand>> Commands;
	UPROPERTY()
	TObjectPtr<UCY_FadeCommand> FadeWidgetCommand = nullptr;
	UPROPERTY()
	TObjectPtr<class UCY_Widget_DialogScreenFader> DialogScreenFader = nullptr;

#define CREATE_FADE_COMMAND(CommandName) \
						TObjectPtr<class UCY_FadeCommand> CommandName = CY_NewObject<UCY_FadeCommand>(); \
						CommandName->AddToRoot(); \
						CommandName->SetCreateFrom(__FILE__, __LINE__);
};
