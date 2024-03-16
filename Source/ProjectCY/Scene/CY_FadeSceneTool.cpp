// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_FadeSceneTool.h"

#include "CY_BuiltInWidgetTool.h"
#include "CY_FadeCommand.h"
#include "CY_StateMachine.h"
#include "CY_WidgetManager.h"
#include "CY_Widget_DialogScreenFader.h"
#include "CY_Widget_Loading.h"

void UCY_FadeSceneTool::Request(UCY_FadeCommand* Command)
{
	Commands.Emplace(Command);

	if(CurrentStep == ECY_FadeStep::Ready)
	{
		StartFadeIn();
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
    			Command->OnFadeInComplete.ExecuteIfBound();
    			Command->OnFadeInComplete.Unbind();
    		}
    
    		bLoadComplete = true;
    	}	
	}
}

void UCY_FadeSceneTool::StartFadeIn()
{
	if(Commands.Num() <= 0)
	{
		return;
	}

	for(int32 i = 0 ; i < Commands.Num() ; ++i)
	{
		TObjectPtr<UCY_FadeCommand> Command = Commands[i].Get();
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
		Command->OnFadeOutStart.ExecuteIfBound();
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
		UCY_Widget_DialogScreenFader* DialogScreenFader = gWidgetMng.GetBuiltInWidgetTool()->GetDialogScreenFader();
		if(DialogScreenFader == nullptr)
		{
			return;
		}

		DialogScreenFader->StartScreenFade(bFadeIn ? ECY_FadeType::FadeIn : ECY_FadeType::FadeOut,
			FBuiltInFadeDelegate::CreateUObject(this, &UCY_FadeSceneTool::OnWidgetFadeInFinished),
						 FBuiltInFadeDelegate::CreateUObject(this, &UCY_FadeSceneTool::OnWidgetFadeOutFinished));
	}
}

void UCY_FadeSceneTool::OnWidgetFadeInFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeIn)
	{
		CurrentStep = ECY_FadeStep::ExitFadeIn;
		bLoadStart = true;
	}
}

void UCY_FadeSceneTool::OnWidgetFadeOutFinished()
{
	if(CurrentStep == ECY_FadeStep::EnterFadeOut)
	{
		CurrentStep = ECY_FadeStep::ExitFadeOut;

		if(FadeWidgetCommand && FadeWidgetCommand->GetLoadingPageType() != ECY_LoadingPageType::None)
		{
			const TObjectPtr<UCY_Widget_Loading> LoadingWidget = gWidgetMng.GetBuiltInWidgetTool()->GetLoadingWidget();
			if(LoadingWidget == nullptr)
			{
				return;
			}
			LoadingWidget->SetLoadingData(FadeWidgetCommand->GetLoadingPageType());
			LoadingWidget->ShowLoading();
		}

		PlayFadeAnimation(FadeWidgetCommand->GetFadeType(), false, false);
	}
}
