// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_SingletonManager.h"

#include "CY_Define.h"
#include "CY_ContentsProcessManager.h"
#include "CY_WidgetManager.h"

TObjectPtr<UCY_SingletonManager> UCY_SingletonManager::Instance = nullptr;

TObjectPtr<UCY_SingletonManager> UCY_SingletonManager::CreateInstance()
{
    Instance = CY_NewObject<UCY_SingletonManager>();
    Instance->AddToRoot();
    Instance->RegisterSingletons();
    Instance->RegisterSingletonsForTick();
    return Instance;
}

void UCY_SingletonManager::DestroyInstance()
{
    if (IsValid(Instance))
    {
        Instance->RemoveSingletons();
        Instance->RemoveFromRoot();
        CY_DeleteObject(Instance);
        Instance = nullptr;
    }
}

void UCY_SingletonManager::BuiltInInitializeSingletons()
{
    for (TObjectPtr<ISingleton> Singleton : Singletons)
    {
        Singleton->BuiltInInitialize();
    }

    bIsBuiltInInitialized = true;
}

void UCY_SingletonManager::TickSingletons(float DeltaTime)
{
    if (bInitialized)
    {
        for (TObjectPtr<ISingleton> Singleton : SingletonsForTick)
        {
            Singleton->Tick(DeltaTime);
        }
    }
}

void UCY_SingletonManager::RemoveSingletons()
{
    Singletons.Reset();
    SingletonsForTick.Reset();

    UCY_ContentsProcessManager::RemoveInstance();
    UCY_WidgetManager::RemoveInstance();
}

void UCY_SingletonManager::FinalizeSingletons()
{
    if (bInitialized == false)
    {
        return;
    }

    for (TObjectPtr<ISingleton> Singleton : Singletons)
    {
        Singleton->PreFinalize();
        Singleton->Finalize();
        Singleton->BuiltInFinalize();
    }
}

void UCY_SingletonManager::RegisterSingletons()
{
    Singletons.Reset();

    Singletons.Emplace(UCY_ContentsProcessManager::MakeInstance());
    Singletons.Emplace(UCY_WidgetManager::MakeInstance());
}

void UCY_SingletonManager::RegisterSingletonsForTick()
{
    SingletonsForTick.Reset();

    SingletonsForTick.Emplace(UCY_ContentsProcessManager::GetInstance());
    SingletonsForTick.Emplace(UCY_WidgetManager::GetInstance());
}
