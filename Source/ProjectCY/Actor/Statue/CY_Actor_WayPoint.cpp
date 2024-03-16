// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Actor_WayPoint.h"

#include "CY_UnitManager.h"
#include "CY_Unit_WayPoint.h"
#include "Character/CY_CharacterBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"


ACY_Actor_WayPoint::ACY_Actor_WayPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;
		FName Id_SpawnNpcActor;
		FText Name_SpawnNpcActor;

		FConstructorStatics() : TextureFinder(TEXT("Texture2D'/Game/EditorResources/S_SpawnStatus.S_SpawnStatus")),
								Id_SpawnNpcActor(TEXT("S_SpawnStatus")),
								Name_SpawnNpcActor(NSLOCTEXT("SpriteCategory", "S_SpawnStatus", "S_SpawnStatus")) {}
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

		ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent0"));
		if (ArrowComponent)
		{
			ArrowComponent->ArrowColor = FColor(0, 255, 128);

			ArrowComponent->ArrowSize = 1.5f;
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

void ACY_Actor_WayPoint::BeginPlay()
{
	
	SpawnStatue();	
}

TObjectPtr<AActor> ACY_Actor_WayPoint::SpawnStatue() const
{
	const TObjectPtr<UCY_Unit_WayPoint> Statue = Cast<UCY_Unit_WayPoint>(gUnitMng.CreateUnit(WayPointIndex, UCY_Unit_WayPoint::StaticClass(), GetActorLocation(), GetActorRotation()));
	if(Statue)
	{
		return nullptr;
	}

	const TObjectPtr<ACY_CharacterBase> StatueActor = Statue->GetCharacterActor();
	if(StatueActor == nullptr)
	{
		return nullptr;
	}

	TArray<FName>& ComponentTags = StatueActor->GetRootComponent()->ComponentTags;


	return StatueActor;
}
