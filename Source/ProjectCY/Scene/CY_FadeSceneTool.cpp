// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_FadeSceneTool.h"

#include "CY_BasePlayer.h"
#include "CY_BasicGameUtility.h"
#include "CY_BuiltInWidgetTool.h"
#include "CY_CameraManager.h"
#include "CY_FadeCommand.h"
#include "CY_Mapper_Common.h"
#include "CY_TableManager.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_DialogScreenFader.h"
#include "CY_Widget_Loading.h"

void UCY_FadeSceneTool::Initialize()
{
	DialogScreenFader = gWidgetMng.GetBuiltInWidgetTool()->GetDialogScreenFader();
	
	if(const TObjectPtr<UCY_Mapper_Common> CommonMapper = Cast<UCY_Mapper_Common>(gTableMng.GetTableMapper(ECY_TableDataType::Common)))
	{
		LoadingMinimumTime = CommonMapper->GetParam03(CommonContents::Loading_Minimum_Time);		
	}
}

void UCY_FadeSceneTool::RegistLevelPath(uint8 SceneId)
{
	const FString Path = gTableMng.GetPath(ECY_TableDataType::BasePath_Level_File, SceneId);
	if(Path.IsEmpty())
	{
		return;
	}
	
	LevelsPath.Emplace(SceneId, Path);
}

void UCY_FadeSceneTool::Request(UCY_FadeCommand* Command)
{
	Commands.Emplace(Command);

	if(Command->GetFadeType() == ECY_FadeStyle::ForceDroneFadeIn)
	{
		FadeWidgetCommand = Command;
		CurrentStep = ECY_FadeStep::EnterFadeIn;
		StartFadeIn();
		return;
	}
	
	if(CurrentStep == ECY_FadeStep::Ready)
	{
		StartFadeOut();
	}
}

void UCY_FadeSceneTool::FinishRequest()
{
	CurrentStep = ECY_FadeStep::Ready;
	bLoadStart = false;
	bLoadComplete = false;
	LoadingMinimumTime = 0.f;
	LoadElapsedTime = 0.f;

	const int32 CommandsNum = Commands.Num();
	for(int32 i = 0 ; i < CommandsNum; i++)
	{
		Commands[0]->RemoveFromRoot();
		CY_DeleteObject(Commands[0]);
		Commands.RemoveAt(0);
	}
}

void UCY_FadeSceneTool::Tick(float DeltaTime)
{
	if(bLoadComplete)
	{
		if(CurrentStep == ECY_FadeStep::ExitFadeOut)
		{
			CurrentStep = ECY_FadeStep::EnterFadeIn;
			StartFadeIn();
			return;
		}
	}
	else
	{
		if(bLoadStart)
    	{
    		LoadElapsedTime += DeltaTime;
    		for(int32 i = 0 ; i < Commands.Num() ; ++i)
    		{
			    const TObjectPtr<UCY_FadeCommand> Command = Commands[i];
    			if(Command->OnFadeOutComplete.IsBound())
    			{
    				Command->OnFadeOutComplete.Execute();
    				Command->OnFadeOutComplete.Unbind();
    			}
    			if(Command->OnCheckLoadComplete.IsBound())
    			{
    				if(Command->OnCheckLoadComplete.Execute() == false)
    				{
    					return;
    				}
    			}

    			if(Command->GetLoadingPageType() != ECY_LoadingPageType::None)
    			{
    				if(LoadingMinimumTime <= LoadElapsedTime)
    				{
    					bLoadComplete = true;
    				}
    			}
			    else
			    {
    				bLoadComplete = true;
			    }
    		}
    	}	
	}
}

FString UCY_FadeSceneTool::GetLevelPath(ECY_GameSceneType SceneType)
{
	const FString* pLevelPath = LevelsPath.Find(static_cast<uint8>(SceneType));

	return pLevelPath ? *pLevelPath : FString();
}

void UCY_FadeSceneTool::StartFadeOut()
{
	if(Commands.Num() <= 0)
	{
		return;
	}

	for(int32 i = 0 ; i < Commands.Num() ; ++i)
	{
		const TObjectPtr<UCY_FadeCommand> Command = Commands[i].Get();
		if(Command->GetFadeType() != ECY_FadeStyle::None)
		{
			FadeWidgetCommand = Command;
			break;
		}
	}

	if(FadeWidgetCommand == nullptr)
	{
		return;
	}

	CurrentStep = ECY_FadeStep::EnterFadeOut;

	if(FadeWidgetCommand->GetFadeType() == ECY_FadeStyle::Drone)
	{
		PlayDrone(true);
	}
	else
	{
		PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), true, FadeWidgetCommand->GetIsDirectFadeOut());
	}
}

void UCY_FadeSceneTool::StartFadeIn()
{
	for(const TObjectPtr<UCY_FadeCommand> Command : Commands)
	{
		if(Command->OnFadeInStart.IsBound())
		{
			Command->OnFadeInStart.Execute();
		}
	}

	if(FadeWidgetCommand)
	{
		if(FadeWidgetCommand->GetFadeType() == ECY_FadeStyle::Drone || FadeWidgetCommand->GetFadeType() == ECY_FadeStyle::ForceDroneFadeIn)
		{
			PlayDrone(false);
		}
		else
		{
			PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), false , false);
		}
	}
}

void UCY_FadeSceneTool::PlayFadeAnimation(ECY_FadeStyle FadeType, bool bFadeIn, bool bDirectFadeIn)
{
	if(FadeType == ECY_FadeStyle::Dialog)
	{
		if(DialogScreenFader == nullptr)
		{
			return;
		}

		DialogScreenFader->Active(true);
		
		if(bFadeIn)
		{
			DialogScreenFader->StartScreenFade(ECY_FadeType::FadeIn,[this](){ OnWidgetFadeOutFinished();});	
		}
		else
		{
			DialogScreenFader->StartScreenFade(ECY_FadeType::FadeOut,[this](){ OnWidgetFadeInFinished();});
		}
		
	}
}

void UCY_FadeSceneTool::PlayDrone(bool bIsFadeOut /* = true */)
{
	gCameraMng.ShowCameraFadeStep([this, bIsFadeOut]()
	{
		bIsFadeOut ? OnCameraFadeOutFinished() : OnCameraFadeInFinished();
	}, bIsFadeOut);
}

void UCY_FadeSceneTool::OnWidgetFadeOutFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeOut)
	{
		CurrentStep = ECY_FadeStep::ExitFadeOut;
		if(!FadeWidgetCommand)
		{
			return;
		}
		
		if(FadeWidgetCommand->GetFadeType() == ECY_FadeStyle::Dialog)
		{
			if(FadeWidgetCommand->GetLoadingPageType() != ECY_LoadingPageType::None)
			{
				const TObjectPtr<UCY_Widget_Loading> LoadingWidget = gWidgetMng.GetBuiltInWidgetTool()->GetLoadingWidget();
				if(LoadingWidget == nullptr)
				{
					return;
				}
				LoadingWidget->SetLoadingData(FadeWidgetCommand->GetLoadingPageType());
				LoadingWidget->ShowLoading();

				//PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), false, false);
			}
			else
			{
				bLoadStart = true;
			}	
		}
	}
}

void UCY_FadeSceneTool::OnWidgetFadeInFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeIn)
	{
		CurrentStep = ECY_FadeStep::ExitFadeIn;
		for(const TObjectPtr<UCY_FadeCommand> Command : Commands)
		{
			if(Command->OnFadeInComplete.IsBound())
			{
				Command->OnFadeInComplete.Execute();
			}
		}

		FinishRequest();
	}
}

void UCY_FadeSceneTool::OnCameraFadeOutFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeOut)
	{
		CurrentStep = ECY_FadeStep::ExitFadeOut;

		// 맵 위젯 활성화
		if(FadeWidgetCommand->GetLoadingPageType() == ECY_LoadingPageType::ShowWorldMap)
		{
			if(const TObjectPtr<UCY_Widget_WorldMap> WorldMap = gWidgetMng.GetBuiltInWidgetTool()->GetWorldMapWidget())
			{
				
				WorldMap->RebuildWorldMap();
				WorldMap->EnableMoveFast(true);
				
				WorldMap->OnFinishedWorldMapFunc([this]()
				{
					if(const TObjectPtr<UCY_BasePlayer> PlayerUnit = Cast<UCY_BasePlayer>(UCY_BasicGameUtility::GetCurrentPlayerUnit()))
					{
						PlayerUnit->SetActionState(ECY_UnitActionState::Player_Normal);
					}
					bLoadComplete = true;
				});
			}		
		}
	}
}

void UCY_FadeSceneTool::OnCameraFadeInFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeIn)
	{
		CurrentStep = ECY_FadeStep::ExitFadeIn;

		// 메인카메라로 다시 전환
		for(const TObjectPtr<UCY_FadeCommand> Command : Commands)
		{
			if(Command->OnFadeInComplete.IsBound())
			{
				Command->OnFadeInComplete.Execute();
			}
		}

		FinishRequest();
	}
}
