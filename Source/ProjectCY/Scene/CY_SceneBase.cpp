// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SceneBase.h"

void UCY_SceneBase::TickLoading(float Delta)
{
	if (LoadingProcessDelegates.IsValidIndex(0) == true)
	{
		if (LoadingProcessDelegates[0].Execute(Delta) == true)
		{
			LoadingProcessDelegates.RemoveAt(0);
		}
	}
}

bool UCY_SceneBase::IsCompleteLoading()
{
	return false;
}

void UCY_SceneBase::Begin()
{
	LoadingProcessDelegates.Empty();
	LoadingProcessDelegates.Add(FCY_LoadingProcessDelegate::CreateUObject(this, &UCY_SceneBase::LoadingPreProcess));
	LoadingProcessDelegates.Add(FCY_LoadingProcessDelegate::CreateUObject(this, &UCY_SceneBase::LoadingProcess));
	LoadingProcessDelegates.Add(FCY_LoadingProcessDelegate::CreateUObject(this, &UCY_SceneBase::LoadingPostProcess));
}

void UCY_SceneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UCY_SceneBase::Exit()
{
	LoadingProcessDelegates.Empty();
}

bool UCY_SceneBase::LoadingPreProcess(float DeltaTime)
{
	return true;
}

bool UCY_SceneBase::LoadingProcess(float DeltaTime)
{
	return true;
}

bool UCY_SceneBase::LoadingPostProcess(float DeltaTime)
{
	return true;
}
