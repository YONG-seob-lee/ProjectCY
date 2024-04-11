// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_State_PlayerNormal.h"

#include "CY_ActorBase.h"
#include "CY_BasePlayer.h"
#include "CY_BasicGameUtility.h"
#include "CY_CameraActor.h"
#include "CY_CameraManager.h"
#include "CY_FadeCommand.h"
#include "CY_FadeSceneTool.h"
#include "CY_InputManager.h"
#include "CY_SceneManager.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_WorldMap.h"
#include "Resource_Unit.h"

void UCY_State_PlayerNormal::Begin()
{
	OwnerUnit = CastChecked<UCY_BasePlayer>(GetOuter());
	if(OwnerUnit == nullptr)
	{
		return;
	}
	CameraActor = gCameraMng.GetCurrentActiveCameraActor();

	WalkSpeed = OwnerUnit->GetResourceUnitData()->WalkSpeed;
	RunSpeed = OwnerUnit->GetResourceUnitData()->RunSpeed;
	SprintSpeed = OwnerUnit->GetResourceUnitData()->SprintSpeed;

	// Bind Axis Key ( WASD , ULDR )
	FInputAxisUnifiedDelegate UpDownDelegate;
	UpDownDelegate.BindDelegate(this, &UCY_State_PlayerNormal::OnAxisUpDown);
	gInputMng.RegistAxis(ECY_Axis_Type::Left, ECY_Action_Type::ActionUpDown, UpDownDelegate);

	FInputAxisUnifiedDelegate LeftRightDelegate;
	LeftRightDelegate.BindDelegate(this, &UCY_State_PlayerNormal::OnAxisLeftRight);
	gInputMng.RegistAxis(ECY_Axis_Type::Left, ECY_Action_Type::ActionLeftRight, LeftRightDelegate);

	// Bind ActionThing ( F key : Interaction , M key : WorldMap )
	gInputMng.RegistInteractionButton(FSimpleDelegate::CreateUObject(this, &UCY_State_PlayerNormal::OnClickInteraction));
	gInputMng.RegistWorldMapButton(FSimpleDelegate::CreateUObject(this, &UCY_State_PlayerNormal::OnClickWorldMap));
}

void UCY_State_PlayerNormal::Tick(float DeltaTime)
{
	if(CameraActor == nullptr)
	{
		CameraActor = gCameraMng.GetCurrentActiveCameraActor();
	}
	
	if(OwnerUnit)
	{
		PlayerMove();
		InteractionProcess();
	}
}

void UCY_State_PlayerNormal::Exit()
{
	Super::Exit();
}

void UCY_State_PlayerNormal::PlayerMove()
{
	const TObjectPtr<ACY_CharacterBase> Character = OwnerUnit->GetCharacterBase();
	if(Character == nullptr)
	{
		return;
	}

	const float DetectJoyStickValue = JoyStickDistance.Size();

	// Step 1. 카메라의 정면벡터가 캐릭터의 정면벡터가 될 수 있게 캐싱
	if(CameraActor == nullptr)
	{
		return;
	}
		
	if(CachedUnitForward == FVector::ZeroVector || CachedUnitRight == FVector::ZeroVector)
	{
		CachedUnitForward = CameraActor->GetForward();
		CachedUnitRight= CameraActor->GetCross();
	}
	
	// Step 2. 캐릭터 정면벡터와 조이스틱을 바인딩
	if(DetectJoyStickValue > 0.001f)
	{
		FVector NewMoveDirection = JoyStickDistance.Y * CachedUnitForward + JoyStickDistance.X * CachedUnitRight;
		CY_LOG(TEXT("%f"), NewMoveDirection.Size());
		NewMoveDirection.Z = 0.f;
		
		FRotator Rotator = NewMoveDirection.Rotation();
		
		// 시계, 반시계
		
		NewMoveDirection.Normalize();
		
		OwnerUnit->SetMoveSpeed(DetectJoyStickValue <= 0.5f ? WalkSpeed : RunSpeed);
		Character->MoveDirection(NewMoveDirection);
	}
	// Step 3. 캐릭터가 더이상 움직이지 않으면 캐싱데이터 제거 및 캐릭터 속도 0 ( 나중에 속도 감쇠 기능 추가해야할 듯 싶음 - 캐릭터 방향성 래깅도 필요해보임)
	else
	{
		CachedUnitForward = FVector::ZeroVector;
		CachedUnitRight = FVector::ZeroVector;
		OwnerUnit->SetMoveSpeed(0.f);
	}
	JoyStickDistance = FVector2d::ZeroVector;
}

void UCY_State_PlayerNormal::InteractionProcess()
{
	if(CameraActor == nullptr)
	{
		CameraActor = gCameraMng.GetCurrentActiveCameraActor(); 
	}
	constexpr float LineTraceDistance = 3000.f;
	const FVector LineTraceStartLocation = CameraActor->GetActorLocation();
	const FVector LineTraceEndLocation = LineTraceStartLocation + CameraActor->GetActorForwardVector() * LineTraceDistance;
	FHitResult HitResult;
	FCollisionQueryParams asdf;
	
	if(CameraActor->ActorLineTraceSingle(HitResult, LineTraceStartLocation, LineTraceEndLocation, ECollisionChannel::ECC_GameTraceChannel1, FCollisionQueryParams::DefaultQueryParam))
	{
		if(TObjectPtr<ACY_ActorBase> TargetActor =  Cast<ACY_ActorBase>(HitResult.GetActor()))
		{
			switch(TargetActor->GetInteractionType())
			{
			case ECY_InteractionType::Teleport_Map:
				{
					CREATE_FADE_COMMAND(Command);
					Command->SetFadeStyle(ECY_FadeStyle::Drone);
					Command->SetIsDirectFadeIn(false);
					Command->SetLoadingPageType(ECY_LoadingPageType::EnterFirst);
					Command->OnCheckLoadComplete = FCY_FadeCheckLoadDelegate::CreateWeakLambda(this, []()
					{
						// 월드맵이 DeActive 될 때 (Camera Fade In 이 끝날 때 월드맵이 활성화 되어있음 활성화가 끝나는 순간이 Fade Out 을 실행할 차례)
						return gWidgetMng.IsFinishedWorldMapProcess();
					});
            
					gSceneMng.ChangeScene(ECY_GameSceneType::WorldMap, Command);
					break;
				}
			default:
				break;
			}
		}
	}
	else
	{
		OnInteractionCallback = nullptr;
	}
}

void UCY_State_PlayerNormal::OnAxisUpDown(float AxisValue)
{
	if(FMath::IsNearlyEqual(AxisValue, 0.f) == false)
	{
		JoyStickDistance.Y = AxisValue;
	}
}

void UCY_State_PlayerNormal::OnAxisLeftRight(float AxisValue)
{
	if(FMath::IsNearlyEqual(AxisValue, 0.f) == false)
	{
		JoyStickDistance.X = AxisValue;
	}
}

void UCY_State_PlayerNormal::OnClickInteraction()
{
	// Reset Input Keys
	OwnerUnit->SetActionState(ECY_UnitActionState::None);

	// Play Fade & Change Scene
	CREATE_FADE_COMMAND(Command);
	Command->SetFadeStyle(ECY_FadeStyle::Drone);
	Command->SetIsDirectFadeIn(false);
	Command->SetLoadingPageType(ECY_LoadingPageType::ShowWorldMap);
	Command->OnCheckLoadComplete = FCY_FadeCheckLoadDelegate::CreateWeakLambda(this, []()
	{
		// 월드맵이 DeActive 될 때 (Camera Fade In 이 끝날 때 월드맵이 활성화 되어있음 활성화가 끝나는 순간이 Fade Out 을 실행할 차례)
		return gWidgetMng.IsFinishedWorldMapProcess();
	});
            
	gSceneMng.ChangeScene(ECY_GameSceneType::WorldMap, Command);
	
	// Step 1. Check Enable Interaction
	if(OnInteractionCallback)
	{
		OnInteractionCallback();
	}
	// Step 2. Check Binding

	// Step 3. BroadCast
}

void UCY_State_PlayerNormal::OnClickWorldMap()
{
	if(const TObjectPtr<UCY_Widget_WorldMap> WorldMapWidget = gWidgetMng.GetBuiltInWidgetTool()->GetWorldMapWidget())
	{
		if(WorldMapWidget->IsVisible())
		{
			WorldMapWidget->ActiveDirect(false);
			WorldMapWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			WorldMapWidget->SetVisibility(ESlateVisibility::Visible);
			WorldMapWidget->ActiveDirect(true);
		}
	}
}
