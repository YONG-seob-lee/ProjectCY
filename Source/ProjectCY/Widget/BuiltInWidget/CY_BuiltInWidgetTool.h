// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget_NpcInteraction.h"
#include "CY_Widget_WorldMap.h"
#include "UObject/Object.h"
#include "CY_BuiltInWidgetTool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_BuiltInWidgetTool : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE TObjectPtr<class UCY_Widget_DialogScreenFader> GetDialogScreenFader() const { return DialogScreenFader;}
	FORCEINLINE TObjectPtr<class UCY_Widget_Compass> GetCompassWidget() const { return CompassWidget; }
	FORCEINLINE TObjectPtr<class UCY_Widget_Loading> GetLoadingWidget() const { return LoadingWidget; }
	FORCEINLINE TObjectPtr<UCY_Widget_WorldMap> GetWorldMapWidget() const { return WorldMapWidget; }
	FORCEINLINE TObjectPtr<UCY_Widget_NpcInteraction> GetNpcInteractionWidget() const { return NpcInteractionWidget; }
	
	FORCEINLINE TSharedPtr<class FCY_PreTouchProcessor> GetPreTouchProcessor() const { return PreTouchProcessor; }

	FORCEINLINE bool IsFinishedWorldMapProcess() const { return WorldMapWidget->GetIsActive(); }
	
	void BuiltInitialize();
	void Initialize();
	void Finalize();
	void Tick(float DeltaTime);

private:
	void ProcessBuiltInCompass() const;
	
	UPROPERTY()
	TObjectPtr<UCY_Widget_DialogScreenFader> DialogScreenFader = nullptr;

	UPROPERTY()
	TObjectPtr<UCY_Widget_Compass> CompassWidget = nullptr;
	
	UPROPERTY()
	TObjectPtr<UCY_Widget_Loading> LoadingWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UCY_Widget_WorldMap> WorldMapWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UCY_Widget_NpcInteraction> NpcInteractionWidget = nullptr;
	
	TSharedPtr<FCY_PreTouchProcessor> PreTouchProcessor;
};
