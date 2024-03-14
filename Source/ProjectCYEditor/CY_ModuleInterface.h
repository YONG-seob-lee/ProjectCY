// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Modules/ModuleInterface.h"

class ICY_ModuleListenerInterface
{
public:
	virtual ~ICY_ModuleListenerInterface() = default;
	virtual void OnStartupModule() {}
	virtual void OnShutdownModule() {}
};
/**
 * 
 */
class ICY_ModuleInterface : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		if (!IsRunningCommandlet())
		{
			AddModuleListener();
			for (int32 i = 0; i < ModuleListener.Num(); i++)
			{
				ModuleListener[i]->OnStartupModule();
			}
		}
	}

	virtual void ShutdownModule() override
	{
		for (int32 i = 0; i < ModuleListener.Num(); i++)
		{
			ModuleListener[i]->OnShutdownModule();
		}
	}

	virtual void AddModuleListener() {}

protected:
	TArray<TSharedRef<ICY_ModuleListenerInterface>> ModuleListener;
};
