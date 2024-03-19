// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Scene_PalWorld.h"

#include "CY_Actor_TeleportPoint.h"
#include "CY_GameInstance.h"
#include "CY_UnitManager.h"
#include "CY_BasePlayer.h"
#include "CY_CameraManager.h"
#include "CY_SceneDefine.h"
#include "EngineUtils.h"
#include "Character/CY_CharacterBase.h"

UCY_Scene_PalWorld::UCY_Scene_PalWorld()
{
}

UCY_Scene_PalWorld::~UCY_Scene_PalWorld()
{
}

void UCY_Scene_PalWorld::Begin()
{
	Super::Begin();

	const TObjectPtr<UWorld> World = gInstance.GetWorld();
	for(TActorIterator<ACY_Actor_TeleportPoint> Iter(World); Iter; ++Iter)
	{
		const TObjectPtr<ACY_Actor_TeleportPoint> TeleportPoint = *Iter;
		if(TeleportPoint && TeleportPoints.Contains(TeleportPoint->GetTeleportPointId()) == false)
		{
			TeleportPoints.Emplace(TeleportPoint->GetTeleportPointId(), TeleportPoint->GetTransform());
		}
	}
}

void UCY_Scene_PalWorld::Exit()
{
	Super::Exit();
}

void UCY_Scene_PalWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UCY_Scene_PalWorld::CreatePlayer()
{
	if(Player.IsValid() == false)
	{
		const TObjectPtr<UCY_BasePlayer> NewPlayer = Cast<UCY_BasePlayer>(gUnitMng.CreateUnit(1, UCY_BasePlayer::StaticClass()));
		if(NewPlayer == nullptr)
		{
			return;
		}
		DestroyPlayer();
		
		Player = NewPlayer;
		Player->SetSelfPlayer(true);
		// Player->SetPlayerName();
		// Player->SetPlayerTitle();
		// Player->ChangeActionState();

		if(const TObjectPtr<ACY_CharacterBase> Character = Player->GetCharacterActor())
		{
			Character->GetRootComponent()->ComponentTags.Emplace(FName("PalWorld.Player"));
		}

		gCameraMng.ChangeCamera(static_cast<uint8>(ECY_GameCameraType::PalWorld));
	}
}

void UCY_Scene_PalWorld::DestroyPlayer()
{
	if(Player.IsValid() == false)
	{
		return;
	}

	//Player->SetAutoMovement(false, nullptr);
	Player->SetActorEnableCollision(false);
	Player->ClearComponentOverlaps();
	Player->SetSelfPlayer(false);

	gUnitMng.DestroyUnit(Player->GetUnitHandle());
	Player.Reset();
}
