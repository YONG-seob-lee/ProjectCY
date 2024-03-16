// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_ActorBase.h"
#include "CY_Actor_WayPoint.generated.h"

UCLASS(BlueprintType)
class PROJECTCY_API ACY_Actor_WayPoint : public ACY_ActorBase
{
	GENERATED_BODY()

public:
	ACY_Actor_WayPoint(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = APC_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 WayPointIndex = 0;

	UPROPERTY(Category = APC_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bLockNpaCamera = false;

	UPROPERTY(Category = APC_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Tag;

	UPROPERTY(Category = APC_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UArrowComponent> TalkArrowComponent;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<class UBillboardComponent> SpriteComponent = nullptr;
	UPROPERTY()
	TObjectPtr<class UArrowComponent> ArrowComponent = nullptr;
#endif

	
protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<AActor> SpawnStatue() const;
};
