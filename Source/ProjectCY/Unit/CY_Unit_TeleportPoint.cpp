// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Unit_TeleportPoint.h"

#include "CY_BasePlayer.h"
#include "CY_BasicGameUtility.h"
#include "CY_TableManager.h"
#include "CY_WidgetManager.h"
#include "Npc.h"
#include "Components/SphereComponent.h"

namespace ComponentTagName
{
	const FName Interaction = TEXT("Collision_Interaction_Component");
}

void UCY_Unit_TeleportPoint::Initialize()
{
	Super::Initialize();
}

void UCY_Unit_TeleportPoint::Finalize()
{
	Super::Finalize();

	if(Collision_Interaction)
	{
		Collision_Interaction->OnComponentBeginOverlap.RemoveAll(this);
		Collision_Interaction->OnComponentEndOverlap.RemoveAll(this);	
	}
}

void UCY_Unit_TeleportPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool UCY_Unit_TeleportPoint::CreateUnit(int32 UnitId, const FVector& Position, const FRotator& Rotator)
{
	Super::CreateUnit(UnitId, Position, Rotator);
	NpcData = gTableMng.GetTableRowData<FNpc>(ECY_TableDataType::Npc, UnitId);
	if(NpcData == nullptr)
	{
		CY_CHECK(false);
		return false;
	}
	
	NpcRoleType = NpcData->Role_Type;

	if(NpcRoleType == NpcRoleType::Interaction)
	{
		BindCollisionComponent_Interaction(NpcData->Interaction_Radius);
	}

	return true;
}

void UCY_Unit_TeleportPoint::DestroyUnit()
{
	Super::DestroyUnit();
}

void UCY_Unit_TeleportPoint::BindCollisionComponent_Interaction(const float SphereRadius)
{
	Collision_Interaction = Cast<USphereComponent>(GetActorComponentByTag(USphereComponent::StaticClass(), ComponentTagName::Interaction));
	if(Collision_Interaction == nullptr)
	{
		return;
	}

	Collision_Interaction->SetSphereRadius(SphereRadius);
	Collision_Interaction->OnComponentBeginOverlap.AddDynamic(this, &UCY_Unit_TeleportPoint::OnNpcInteractionBeginOverlap);
	Collision_Interaction->OnComponentEndOverlap.AddDynamic(this, &UCY_Unit_TeleportPoint::OnNpcInteractionEndOverlap);
	Collision_Interaction->SetGenerateOverlapEvents(true);
}

void UCY_Unit_TeleportPoint::OnNpcInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
#if WITH_EDITOR
	UCY_BasicGameUtility::ShowMessageOnScreen(TEXT("UCY_Unit_TeleportPoint::OnNpcInteractionBeginOverlap"));
#endif
	
	const TObjectPtr<ACY_CharacterBase> PlayerCharacter = Cast<ACY_CharacterBase>(OtherActor);
	if(PlayerCharacter == nullptr)
	{
		return;
	}

	const TObjectPtr<UCY_BasePlayer> Player = Cast<UCY_BasePlayer>(PlayerCharacter->GetOwnerUnitBase());
	if(Player == nullptr)
	{
		return;
	}

	if(NpcRoleType == NpcRoleType::Interaction)
	{
		// Step 1. Process Actor ( If Interaction Role Is It, Do not Anything)
		Player->BindInteractionEvent();
		// Step 2. Process Widget
		gWidgetMng.OnNpcInteractionOverlap(NpcData->UnitId, true);		
	}
}

void UCY_Unit_TeleportPoint::OnNpcInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const TObjectPtr<ACY_CharacterBase> PlayerCharacter = Cast<ACY_CharacterBase>(OtherActor);
	if(PlayerCharacter == nullptr)
	{
		return;
	}

	const TObjectPtr<UCY_BasePlayer> Player = Cast<UCY_BasePlayer>(PlayerCharacter->GetOwnerUnitBase());
	if(Player == nullptr)
	{
		return;
	}

	if(NpcRoleType == NpcRoleType::Interaction)
	{
		// Step 1. UnBind Actor Event
		Player->UnBindInteractionEvent();
		// Step 2. Finish Widget Process		
		gWidgetMng.OnNpcInteractionOverlap(NpcData->UnitId, false);		
	}
}
