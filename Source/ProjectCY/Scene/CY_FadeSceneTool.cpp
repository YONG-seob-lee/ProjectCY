// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_FadeSceneTool.h"

#include "CY_BuiltInWidgetTool.h"
#include "CY_FadeCommand.h"
#include "CY_Mapper_Common.h"
#include "CY_StateMachine.h"
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

	if(CurrentStep == ECY_FadeStep::Ready)
	{
		StartFadeIn();
	}
}

void UCY_FadeSceneTool::FinishRequest()
{
	CurrentStep = ECY_FadeStep::Ready;

	for(int32 i = 0 ; i < Commands.Num(); i++)
	{
		Commands[i]->RemoveFromRoot();
		CY_DeleteObject(Commands[i]);
		Commands.RemoveAt(i);
	}
}

void UCY_FadeSceneTool::Tick(float DeltaTime)
{
	if(bLoadComplete)
	{
		if(CurrentStep == ECY_FadeStep::ExitFadeIn)
		{
			CurrentStep = ECY_FadeStep::EnterFadeOut;
			StartFadeOut();
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
    			if(Command->OnFadeInComplete.IsBound())
    			{
    				Command->OnFadeInComplete.Execute();
    				Command->OnFadeInComplete.Unbind();
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

void UCY_FadeSceneTool::StartFadeIn()
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

	CurrentStep = ECY_FadeStep::EnterFadeIn;

	PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), true, FadeWidgetCommand->GetIsDirectFadeIn());
}

void UCY_FadeSceneTool::StartFadeOut()
{
	for(const TObjectPtr<UCY_FadeCommand> Command : Commands)
	{
		if(Command->OnFadeOutStart.IsBound())
		{
			Command->OnFadeOutStart.Execute();
		}
	}

	if(FadeWidgetCommand)
	{
		PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), false , false);
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

		DialogScreenFader->Active(500);
		
		if(bFadeIn)
		{
			DialogScreenFader->StartScreenFade(ECY_FadeType::FadeIn,[this](){ OnWidgetFadeInFinished();});	
		}
		else
		{
			DialogScreenFader->StartScreenFade(ECY_FadeType::FadeOut,[this](){ OnWidgetFadeOutFinished();});
		}
		
	}
}

void UCY_FadeSceneTool::OnWidgetFadeInFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeIn)
	{
		CurrentStep = ECY_FadeStep::ExitFadeIn;
		
		if(FadeWidgetCommand && FadeWidgetCommand->GetLoadingPageType() != ECY_LoadingPageType::None)
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

void UCY_FadeSceneTool::OnWidgetFadeOutFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeOut)
	{
		CurrentStep = ECY_FadeStep::ExitFadeOut;
		for(const TObjectPtr<UCY_FadeCommand> Command : Commands)
		{
			if(Command->OnFadeOutComplete.IsBound())
			{
				Command->OnFadeOutComplete.Execute();
			}
		}

		FinishRequest();
	}
}
