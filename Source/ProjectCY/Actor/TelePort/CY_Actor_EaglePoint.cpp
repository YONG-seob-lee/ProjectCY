// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Actor_EaglePoint.h"

#include "CY_UnitManager.h"
#include "CY_Unit_TeleportPoint.h"
#include "Character/CY_CharacterBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"


ACY_Actor_EaglePoint::ACY_Actor_EaglePoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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

		FConstructorStatics() : TextureFinder(TEXT("Texture2D'/Game/Texture2D/Game/EditorResources/Icon_Potal_Active.Icon_Potal_Active'")),
								Id_SpawnNpcActor(TEXT("Icon_Potal_Active")),
								Name_SpawnNpcActor(NSLOCTEXT("SpriteCategory", "Icon_Potal_Active", "Icon_Potal_Active")) {}
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

void ACY_Actor_EaglePoint::BeginPlay()
{
	SetInteractionType(ECY_InteractionType::Teleport_Map);
	SpawnStatue();	
}

TObjectPtr<AActor> ACY_Actor_EaglePoint::SpawnStatue() const
{
	const TObjectPtr<UCY_Unit_TeleportPoint> Statue = Cast<UCY_Unit_TeleportPoint>(gUnitMng.CreateUnit(WayPointIndex, UCY_Unit_TeleportPoint::StaticClass(), GetActorLocation(), GetActorRotation()));
	if(IsValid(Statue) == false)
	{
		return nullptr;
	}

	const TObjectPtr<ACY_CharacterBase> StatueActor = Statue->GetCharacterBase();
	if(StatueActor == nullptr)
	{
		return nullptr;
	}

	TArray<FName>& ComponentTags = StatueActor->GetRootComponent()->ComponentTags;

	return StatueActor;
}
