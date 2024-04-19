// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_Widget_Title.h"

#include "CommonButtonBase.h"
#include "CY_BasicGameUtility.h"
#include "CY_FadeCommand.h"
#include "CY_FadeSceneTool.h"
#include "CY_SceneManager.h"
#include "Button/CY_TitleButtonBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UCY_Widget_Title::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	if(CPP_StartButton)
	{
		CPP_StartButton->SetButtonText(TEXT("Game Start"));
		UCommonButtonBase::FCommonButtonEvent StartEvent;
		StartEvent.AddUObject(this , &UCY_Widget_Title::OnClickStartButton);
		CPP_StartButton->SetOnClickEvent(StartEvent);
	}

	if(CPP_ExitButton)
	{
		CPP_ExitButton->SetButtonText(TEXT("Exit"));
		UCommonButtonBase::FCommonButtonEvent ExitEvent;
		ExitEvent.AddUObject(this, &UCY_Widget_Title::OnClickExitButton);
		CPP_ExitButton->SetOnClickEvent(ExitEvent);
	}
}

void UCY_Widget_Title::FinishWidget()
{
	Super::FinishWidget();

	CPP_StartButton->UnbindClickEvent();
}

void UCY_Widget_Title::OnClickStartButton()
{
	CREATE_FADE_COMMAND(Command);
	Command->SetFadeStyle(ECY_FadeStyle::Dialog);
	Command->SetIsDirectFadeOut(false);
	Command->SetLoadingPageType(ECY_LoadingPageType::None);
	Command->OnCheckLoadComplete = FCY_FadeCheckLoadDelegate::CreateLambda([]()
	{
		return gSceneMng.IsCompleteChangeScene();
	}) ;
	
	gSceneMng.ChangeScene(ECY_GameSceneType::PalWorld, Command);
}

void UCY_Widget_Title::OnClickExitButton()
{
	UKismetSystemLibrary::QuitGame(this, UCY_BasicGameUtility::GetPlayerController() ,EQuitPreference::Quit, false);
}
