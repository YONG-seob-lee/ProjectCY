// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_BuiltInWidgetTool.h"
#include "CY_Singleton.h"
#include "CY_WidgetDefine.h"
#include "CY_WidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_WidgetManager : public UObject, public UCY_Singleton<UCY_WidgetManager>
{
	GENERATED_BODY()
	
public:
	UCY_WidgetManager();
	virtual ~UCY_WidgetManager() override;

	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	virtual void Tick(float DeltaTime) override;

	void ClearExclusiveLayer();

	TObjectPtr<UCY_Widget> CY_CreateWidget(const FName& TypeName);
	TObjectPtr<UCY_Widget> CY_CreateWidgetNotManaging(const FName& TypeName);
	
	void PreDestroyWidget(TObjectPtr<UCY_Widget> Widget);
	bool DestroyWidget(const FName& TypeName);
	void PostDestroyWidget(const FName& TypeName);
	TObjectPtr<UCY_Widget> GetWidget(const FName& TypeName);
	TObjectPtr<UCY_Widget> CreateWidgetNotManaging(const FString& Path) const;
	TObjectPtr<UCY_Widget> CreateWidgetNotManagingBySOP(const FSoftObjectPath& SoftObjectPath) const;

	void ShowToastMessage(const FString& Message) const;
	void ShowSystemPopup(FCY_SystemPopupParameter& Parameter);
	
	TObjectPtr<UCY_BuiltInWidgetTool> GetBuiltInWidgetTool() const { return BuiltInTool; }

	FORCEINLINE bool IsFinishedWorldMapProcess() const { return BuiltInTool->IsFinishedWorldMapProcess(); }

	FCY_CreateWidget OnCreateWidget;
	FCY_DestroyWidget OnDestroyWidget;


	// Contents
	void OnNpcInteractionOverlap(int32 NpcUnitId, bool bBegin) const;
	
private:
	TObjectPtr<UCY_Widget> CreateWidget_Internal(const FName& TypeName, bool bManaged);
	TObjectPtr<UCY_Widget> CreateWidget_Internal_Managing(const FString& Path);
	TObjectPtr<UCY_Widget> CreateWidget_Internal_NotManaging(const FString& Path) const;
	
	void AddExclusiveLayerWidget(TObjectPtr<UCY_Widget> Widget);
	void RemoveExclusiveLayerWidget(TObjectPtr<UCY_Widget> Widget);

	void LoadComplete(const FString& TableName, TObjectPtr<UObject> WidgetData);

	void ProcessBuiltInCompass();
	
	UPROPERTY()
	TObjectPtr<UCY_BuiltInWidgetTool> BuiltInTool = nullptr;
	
	UPROPERTY()
	TArray<TObjectPtr<UCY_Widget>> ExclusiveLayers;

	UPROPERTY()
	TMap<FName, TWeakObjectPtr<UCY_Widget>> ManagedWidgets;
	
#define gWidgetMng (*UCY_WidgetManager::GetInstance())
};