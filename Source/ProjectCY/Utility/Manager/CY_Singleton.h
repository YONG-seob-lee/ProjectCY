// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ISingleton
{
public:
	virtual ~ISingleton() {}

	virtual void BuiltInInitialize() {}
	virtual void Initialize() {}
	virtual void PostInitialize() {}
	virtual void PreFinalize() {}
	virtual void Finalize() {}
	virtual void BuiltInFinalize() {}

	virtual void Tick(float _DeltaTime) {}
};

/**
 *
 */
template<typename TClass>
class PROJECTCY_API UCY_Singleton : public ISingleton
{
protected:
	static TObjectPtr<TClass> Instance;

public:
	static TClass* MakeInstance();
	static void    RemoveInstance();
	static TObjectPtr<TClass> GetInstance();
	static bool    HasInstance();
};


template<typename TClass>
TObjectPtr<TClass> UCY_Singleton<TClass>::Instance = nullptr;

#include "CY_Singleton.inl"