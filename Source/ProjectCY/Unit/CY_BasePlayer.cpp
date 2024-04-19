// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_BasePlayer.h"

#include "CY_AnimInstance.h"
#include "CY_BasicGameUtility.h"
#include "CY_CameraManager.h"
#include "CY_FadeCommand.h"
#include "CY_FadeSceneTool.h"
#include "CY_SceneManager.h"
#include "CY_StateBase.h"
#include "CY_StateMachine.h"
#include "CY_UnitManager.h"
#include "CY_WidgetManager.h"
#include "Camera/CY_CameraDefine.h"
#include "Character/CY_CharacterBase.h"
#include "UnitState/CY_State_PlayerNormal.h"


void UCY_BasePlayer::Initialize()
{
	Super::Initialize();
}

void UCY_BasePlayer::Finalize()
{
	PlayerStateMachine->Destroy();
	PlayerStateMachine->RemoveFromRoot();
	PlayerStateMachine = nullptr;
	
	Super::Finalize();
}

void UCY_BasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerStateMachine)
	{
		PlayerStateMachine->Tick(DeltaTime);
	}
}

bool UCY_BasePlayer::CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot)
{
	SetUnitHandle(UnitTableId);
	if(Super::CreateUnit(UnitTableId, Pos, Rot) == false)
	{
		return false;
	}

	if(CreateActionStateMachine())
	{
		AddActionState(ECY_UnitActionState::None, TEXT("None"), UCY_StateBase::StaticClass());
		AddActionState(ECY_UnitActionState::Player_Normal, TEXT("Player_Normal"), UCY_State_PlayerNormal::StaticClass());
	}

	ChangeActionState(ECY_UnitActionState::Player_Normal);

	CreatePlayerStateMachine();

	if(CharacterBase.IsValid())
	{
		CharacterBase->SetActiveMovementComponent(true);
	}

	return true;
}

void UCY_BasePlayer::DestroyUnit()
{
	SetUnitHandle(InvalidUnitHandle);
	Super::DestroyUnit();
}

bool UCY_BasePlayer::CreatePlayerStateMachine()
{
	if(GetUnitHandle() == InvalidUnitHandle)
	{
		return false;
	}

	PlayerStateMachine = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	PlayerStateMachine->AddToRoot();
	PlayerStateMachine->Create();

	return true;
}

void UCY_BasePlayer::SetSelfPlayer(bool _bSelfPlayer)
{
	bSelfPlayer = _bSelfPlayer;
}

void UCY_BasePlayer::ChangePlayerState(ECY_UnitState UnitState) const
{
	if(PlayerStateMachine)
	{
		PlayerStateMachine->SetState(UnitState);
	}
}

void UCY_BasePlayer::SetPositionAndRotator(const FVector& Position, const FRotator& Rotator) const
{
	if(const TObjectPtr<ACY_CharacterBase> Character = GetCharacterBase())
	{
		Character->SetPositionAndRotator(Position, Rotator);
	}
}

void UCY_BasePlayer::SetActorEnableCollision(bool bUnitEnableCollision) const
{
	const TObjectPtr<ACY_CharacterBase> Character = GetCharacterBase();
	if (GetUnitHandle() != InvalidUnitHandle && IsValid(Character))
	{
		Character->SetActorEnableCollision(bUnitEnableCollision);
	}
}

void UCY_BasePlayer::ClearComponentOverlaps() const
{
	const TObjectPtr<ACY_CharacterBase> Character = GetCharacterBase();
	if (GetUnitHandle() != InvalidUnitHandle && IsValid(Character))
	{
		Character->ClearComponentOverlaps();
		Character->UpdateOverlaps();
	}
}

void UCY_BasePlayer::SetActionState(ECY_UnitActionState _ActionState) const
{
	ChangeActionState(_ActionState);
}

void UCY_BasePlayer::SetMoveSpeed(float MoveSpeed) const
{
	if(const TObjectPtr<UCY_AnimInstance> AnimInstance = GetAnimInstance())
	{
		AnimInstance->SetMoveSpeed(MoveSpeed);
	}
}

void UCY_BasePlayer::BindInteractionEvent()
{
	if(const TObjectPtr<UCY_State_PlayerNormal> PlayerNormalState = Cast<UCY_State_PlayerNormal>(GetActionState(ECY_UnitActionState::Player_Normal)))
	{
		PlayerNormalState->SetOnInteractionEventFunc([this]()
		{
			// Reset Input Keys & Widgets
			SetActionState(ECY_UnitActionState::None);
			if(const TObjectPtr<UCY_Widget_NpcInteraction> NpcInteractionWidget = gWidgetMng.GetBuiltInWidgetTool()->GetNpcInteractionWidget())
			{
				NpcInteractionWidget->Active(false);
			}

			// Play Fade & Change Scene
			CREATE_FADE_COMMAND(Command);
			Command->SetFadeStyle(ECY_FadeStyle::Drone);
			Command->SetIsDirectFadeOut(false);
			Command->SetLoadingPageType(ECY_LoadingPageType::ShowWorldMap);
			Command->OnCheckLoadComplete = FCY_FadeCheckLoadDelegate::CreateWeakLambda(this, []()
			{
				// 월드맵이 DeActive 될 때 (Camera Fade In 이 끝날 때 월드맵이 활성화 되어있음 활성화가 끝나는 순간이 Fade Out 을 실행할 차례)
				return gWidgetMng.IsFinishedWorldMapProcess();
			});
			Command->OnFadeInComplete = FCY_FadeEventDelegate::CreateWeakLambda(this, []
			{
				gCameraMng.ActiveCamera(ECY_GameCameraType::PalWorld, CameraSubType::Main);
			});
			            
			gSceneMng.ChangeScene(ECY_GameSceneType::WorldMap, Command);
		});
	}
}

void UCY_BasePlayer::UnBindInteractionEvent() const
{
	if(const TObjectPtr<UCY_State_PlayerNormal> PlayerNormalState = Cast<UCY_State_PlayerNormal>(GetActionState(ECY_UnitActionState::Player_Normal)))
	{
		PlayerNormalState->SetOnInteractionEventFunc(nullptr);
	}
}

void UCY_BasePlayer::ChangeActionState(ECY_UnitActionState ActionType) const
{
	UCY_BasicGameUtility::FlushPressedKeys();
	
	Super::ChangeActionState(ActionType);
}
