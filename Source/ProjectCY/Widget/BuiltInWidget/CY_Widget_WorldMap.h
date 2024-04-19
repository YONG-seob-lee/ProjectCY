// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_WorldMap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_WorldMap : public UCY_Widget
{
	GENERATED_BODY()
public:
	FORCEINLINE static FName GetWidgetName() { return TEXT("WorldMap"); }
	
	FORCEINLINE bool GetIsActive() const { return bActive; }
	FORCEINLINE void OnFinishedWorldMapFunc(const TFunction<void()>& Func) { OnFinishedWorldMapProcess = Func; }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void FinishWidget() override;
	
	void RebuildWorldMap(bool _bActive = true);

	void OnClickEaglePoint(TObjectPtr<UCY_Button> Button);

private:
	void SetProjectionVariable();
	void SetTelePortPosition();
	void SetTeleportInitialize();
	
	void RePositionPlayerIcon() const;

	UPROPERTY(Category = CY_Widget_WorldMap, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 IconPathId = 0;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_WorldMapImage = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UNamedSlot> CPP_PlayerNamedSlot = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCY_Widget_WorldMapIcon> CPP_EagleIcon_0 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCY_Widget_WorldMapIcon> CPP_EagleIcon_1 = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCY_Widget_WorldMapIcon> CPP_EagleIcon_2 = nullptr;

	TMap<TObjectPtr<UCY_Widget_WorldMapIcon>, bool> EagleIcons;
	TFunction<void()> OnFinishedWorldMapProcess;

	TWeakObjectPtr<class UCY_UnitBase> PlayerUnit = nullptr;
	
	// Projection Variable
	FVector2d WorldMapCenterVector = FVector2d::ZeroVector;
	FVector2d WorldMapSize = FVector2d::ZeroVector;
	float WorldMapScale = 0.f;
};