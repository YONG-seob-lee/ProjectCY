﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Actor_PlayerSpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"


// Sets default values
ACY_Actor_PlayerSpawnPoint::ACY_Actor_PlayerSpawnPoint(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	const TObjectPtr<USceneComponent> SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	RootComponent->Mobility = EComponentMobility::Static;

#if WITH_EDITORONLY_DATA
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;
		FName Id_SpawnNpcActor;
		FText Name_SpawnNpcActor;

		FConstructorStatics() : TextureFinder(*DefaultImage::Path),
								Id_SpawnNpcActor(DefaultImage::Name),
								Name_SpawnNpcActor(NSLOCTEXT("SpriteCategory", "DefaultImage", "DefaultImage")) {}
	};
	
	if (!IsRunningCommandlet())
	{
		FConstructorStatics ConstructorStatics;
		SpriteComponent = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
		if (SpriteComponent)
		{
			SpriteComponent->Sprite = ConstructorStatics.TextureFinder.Get();
			SpriteComponent->SetRelativeScale3D_Direct(FVector(0.5f, 0.5f, 0.5f));
			SpriteComponent->bHiddenInGame = true;
			SpriteComponent->bIsScreenSizeScaled = true;
			SpriteComponent->SpriteInfo.Category = ConstructorStatics.Id_SpawnNpcActor;
			SpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.Name_SpawnNpcActor;
			SpriteComponent->SetupAttachment(RootComponent);
			SpriteComponent->bReceivesDecals = false;
		}

		ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
		if (ArrowComponent)
		{
			ArrowComponent->ArrowColor = FColor(0, 255, 128);

			ArrowComponent->ArrowSize = 5.f;
			ArrowComponent->bHiddenInGame = true;
			ArrowComponent->bTreatAsASprite = true;
			ArrowComponent->bIsScreenSizeScaled = true;
			ArrowComponent->SpriteInfo.Category = ConstructorStatics.Id_SpawnNpcActor;
			ArrowComponent->SpriteInfo.DisplayName = ConstructorStatics.Name_SpawnNpcActor;
			ArrowComponent->SetupAttachment(RootComponent);
			ArrowComponent->SetUsingAbsoluteScale(true);
		}
	}
#endif
}

// Called when the game starts or when spawned
void ACY_Actor_PlayerSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACY_Actor_PlayerSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
