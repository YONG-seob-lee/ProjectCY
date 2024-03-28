// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CY_ActorBase.h"
#include "CY_Actor_TeleportPoint.generated.h"

namespace DefaultImage
{
	const FString Name = TEXT("DefaultImage");
	const FString Path = TEXT("Texture2D'/Game/Texture2D/Game/EditorResources/DefaultImage.DefaultImage'");	
}

UCLASS(BlueprintType)
class PROJECTCY_API ACY_Actor_TeleportPoint : public ACY_ActorBase
{
	GENERATED_BODY()

public:
	ACY_Actor_TeleportPoint(const FObjectInitializer& ObjectInitializer);
	FORCEINLINE int32 GetTeleportPointId() const { return TeleportPointId; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(Category = ACY_Actor_TeleportPoint, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 TeleportPointId;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UBillboardComponent> SpriteComponent;

	UPROPERTY()
	TObjectPtr<class UArrowComponent> ArrowComponent;
#endif
};
