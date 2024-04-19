// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_WorldMap.h"

#include "CY_Actor_EaglePoint.h"
#include "CY_BasicGameUtility.h"
#include "CY_TableManager.h"
#include "CY_UnitBase.h"
#include "CY_UnitManager.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_WorldMapIcon.h"
#include "EngineUtils.h"
#include "Landscape.h"
#include "Button/CY_Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/NamedSlot.h"

void UCY_Widget_WorldMap::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	if(CPP_PlayerNamedSlot)
	{
		if(const TObjectPtr<UCY_Widget_WorldMapIcon> PlayerIcon = Cast<UCY_Widget_WorldMapIcon>(gWidgetMng.CY_CreateWidget(UCY_Widget_WorldMapIcon::GetWidgetName())))
		{
			const FString IconPath = gTableMng.GetPath(ECY_TableDataType::BasePath_Img_File, IconPathId);
			if(const TObjectPtr<UTexture2D> IconTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *IconPath)))
			{
				PlayerIcon->SetIconTexture(IconTexture);
			}
			CPP_PlayerNamedSlot->AddChild(PlayerIcon);
		}		
	}

	EagleIcons.Emplace(CPP_EagleIcon_0, false);
	EagleIcons.Emplace(CPP_EagleIcon_1, false);
	EagleIcons.Emplace(CPP_EagleIcon_2, false);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UCY_Widget_WorldMap::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(PlayerUnit == nullptr)
	{
		PlayerUnit = UCY_BasicGameUtility::GetCurrentPlayerUnit();
	}

	if(WorldMapCenterVector == FVector2d::ZeroVector)
	{
		SetProjectionVariable();
		SetTelePortPosition();
		SetTeleportInitialize();
	}

	RePositionPlayerIcon();
}

void UCY_Widget_WorldMap::FinishWidget()
{
	PlayerUnit.Reset();
	
	Super::FinishWidget();
}

void UCY_Widget_WorldMap::RebuildWorldMap(bool _bActive /* = true */)
{
	StopAllAnimations();
	
	bActive = _bActive;
	SetVisibility(bActive ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	Active(bActive);
}

void UCY_Widget_WorldMap::OnClickEaglePoint(TObjectPtr<UCY_Button> Button)
{
	
}

void UCY_Widget_WorldMap::SetProjectionVariable()
{
	if(WorldMapSize == FVector2d::ZeroVector)
	{
		if(CPP_WorldMapImage)
		{
			const FGeometry& Geometry = CPP_WorldMapImage->GetCachedGeometry();
			WorldMapSize = Geometry.GetLocalSize();
			WorldMapCenterVector = WorldMapSize * 0.5;
		}	
	}
	
	if(const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld())
	{
		for(TActorIterator<ALandscape> Iter(World); Iter; ++Iter)
		{
			if(const TObjectPtr<ALandscape> LandScape = Cast<ALandscape>(*Iter))
			{
				WorldMapScale = (LandScape->GetActorLocation().X * 2) / WorldMapSize.X;
				if(WorldMapScale < 0)
				{
					WorldMapScale *= -1.f;
				}
			}
		}
	}
}

void UCY_Widget_WorldMap::SetTeleportInitialize()
{
	for(const auto& EagleIcon : EagleIcons)
	{
		EagleIcon.Key->InitializeIcon();

		EagleIcon.Key->SetOnClickAcceptMoveFunction([this](const FVector& SpawnActorPosition)
		{
			// Step 1. 캐릭터 특정 위치로 이동하는 카메라 애니메이션 추가 하는게 좋아보임.

			if(PlayerUnit.IsValid())
			{
				if(SpawnActorPosition == FVector::ZeroVector)
				{
					return;
				}
				
				PlayerUnit->SetUnitPosition(SpawnActorPosition);
		
				// Step 2. 월드맵 제거, 로드 컴플리트
				if(OnFinishedWorldMapProcess)
				{
					RebuildWorldMap(false);
					OnFinishedWorldMapProcess();
				}
			}	
		});
	}
}

void UCY_Widget_WorldMap::SetTelePortPosition()
{
	if(WorldMapCenterVector == FVector2d::ZeroVector)
	{
		return;
	}
	
	if(EagleIcons.Num() > 0)
	{
		if(const TObjectPtr<UWorld> World = UCY_BasicGameUtility::GetGameWorld())
		{
			for(TActorIterator<ACY_Actor_EaglePoint> Iter(World); Iter; ++Iter)
			{
				if(const TObjectPtr<ACY_Actor_EaglePoint> EaglePoint = Cast<ACY_Actor_EaglePoint>(*Iter))
				{
					TObjectPtr<UCY_Widget_WorldMapIcon> TargetEagleIcon = nullptr;
					for(const auto& EagleIcon : EagleIcons)
					{
						if(EagleIcon.Value == false)
						{
							TargetEagleIcon = EagleIcon.Key;
							break;
						}
					}
					
					if(const TObjectPtr<UCanvasPanelSlot> EagleSlot = Cast<UCanvasPanelSlot>(TargetEagleIcon->Slot))
					{
						// 플레이어가 이동해야할 위치 IconWidget 에 데이터 저장.
						const FVector EagleLocation = EaglePoint->GetTargetLocation();
						TargetEagleIcon->SetTargetVector(EaglePoint->GetTargetVector());
						
						const FVector2d EagleIconLocation = FVector2d(EagleLocation.X, EagleLocation.Y) / WorldMapScale + WorldMapCenterVector;
						const FVector2d Size = EagleSlot->GetSize();
						CY_LOG(TEXT("EagleIconLocation = %s "), *EagleIconLocation.ToString());
						EagleSlot->SetPosition(EagleIconLocation - Size * 0.5f);

						EagleIcons.Emplace(TargetEagleIcon, true);
					}
				}
			}
		}	
	}
}

void UCY_Widget_WorldMap::RePositionPlayerIcon() const
{
	if(CPP_PlayerNamedSlot == nullptr)
	{
		return;
	}
	
	if(const TObjectPtr<UCanvasPanelSlot> PlayerSlot = Cast<UCanvasPanelSlot>(CPP_PlayerNamedSlot->Slot))
	{
		if(PlayerUnit.IsValid())
		{
			if(const TObjectPtr<ACY_CharacterBase> CharacterBase = PlayerUnit->GetCharacterBase())
			{
				// Step1. Set PlayerIcon Position
				const FVector PlayerLocation = CharacterBase->GetCurrentLocation();
				const FVector2d PlayerIconLocation = FVector2d(PlayerLocation.X, PlayerLocation.Y) / WorldMapScale + WorldMapCenterVector;
				CY_LOG(TEXT("PlayerIconLocation = %s "), *PlayerIconLocation.ToString());
				const FVector2d Size = PlayerSlot->GetSize();
				PlayerSlot->SetPosition(PlayerIconLocation - Size * 0.5f);

				// Step2. Set PlayIcon Angle
				const FRotator PlayerRotator = CharacterBase->GetCurrentRotator();
				CPP_PlayerNamedSlot->SetRenderTransformAngle(PlayerRotator.Yaw);
			}
		}
	}
}
