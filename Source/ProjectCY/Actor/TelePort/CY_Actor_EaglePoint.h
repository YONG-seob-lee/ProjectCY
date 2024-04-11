// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_Actor_TeleportPoint.h"
#include "CY_Actor_EaglePoint.generated.h"

UCLASS(BlueprintType)
class PROJECTCY_API ACY_Actor_EaglePoint : public ACY_Actor_TeleportPoint
{
	GENERATED_BODY()

public:
	ACY_Actor_EaglePoint(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = ACY_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 WayPointIndex = 0;

	UPROPERTY(Category = ACY_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bLockNpaCamera = false;

	UPROPERTY(Category = ACY_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Tag;

	UPROPERTY(Category = ACY_Actor_WayPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UArrowComponent> TalkArrowComponent = nullptr;
	
protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<AActor> SpawnStatue() const;
};
