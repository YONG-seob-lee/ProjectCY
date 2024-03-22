#pragma once
#include "CY_Define.h"
#include "CY_Singleton.h"

template<typename TClass>
TClass* UCY_Singleton<TClass>::MakeInstance()
{
	if(Instance != nullptr)
	{
		CY_CHECK(Instance != nullptr);
		CY_LOG(TEXT("Wrong Pointer In Here. Please Check Develdoper Name Cheong Ah."));
		return nullptr;
	}

	Instance = CY_NewObject<TClass>();
	Instance->AddToRoot();
	return Instance;
};

template<typename TClass>
void UCY_Singleton<TClass>::RemoveInstance()
{
	if(Instance == nullptr)
	{
		return;
	}

	if(Instance->IsValidLowLevel())
	{
		Instance->RemoveFromRoot();

		CY_DeleteObject(Instance);
	}

	Instance = nullptr;
};

template<typename TClass>
TObjectPtr<TClass> UCY_Singleton<TClass>::GetInstance()
{
	return Instance;
};

template<typename TClass>
bool UCY_Singleton<TClass>::HasInstance()
{
	return Instance != nullptr && !Instance->HasAnyFlags(RF_FinishDestroyed);
};
