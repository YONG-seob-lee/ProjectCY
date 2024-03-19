// Fill out your copyright notice in the Description page of Project Settings.


#include "CY_WidgetManager.h"
#include "CY_StateMachine.h"
#include "CY_Define.h"
#include "CY_GameInstance.h"
#include "CY_Mapper_Resource_Widget.h"
#include "CY_TableManager.h"
#include "CY_Utility.h"
#include "CY_Widget.h"
#include "CY_WidgetDefine.h"

UCY_WidgetManager::UCY_WidgetManager()
{
}

UCY_WidgetManager::~UCY_WidgetManager()
{
}

void UCY_WidgetManager::Initialize()
{
	WidgetMachine = CY_NewObject<UCY_StateMachine>(this, UCY_StateMachine::StaticClass());
	WidgetMachine->AddToRoot();
	WidgetMachine->Create();
}

void UCY_WidgetManager::Finalize()
{
}

void UCY_WidgetManager::Tick(float DeltaTime)
{
	if (WidgetMachine)
	{
		WidgetMachine->Tick(DeltaTime);
	}
}

void UCY_WidgetManager::ClearExclusiveLayer()
{
	constexpr uint8 Top = static_cast<uint8>(ECY_ExclusiveGroup::TopMenu);
	constexpr uint8 Content = static_cast<uint8>(ECY_ExclusiveGroup::ContentMenu);

	if(ExclusiveLayers.IsValidIndex(Top))
	{
		ExclusiveLayers[Top] = nullptr;
	}
	if(ExclusiveLayers.IsValidIndex(Content))
	{
		ExclusiveLayers[Content] = nullptr;
	}
}

TObjectPtr<UCY_Widget> UCY_WidgetManager::CY_CreateWidget(const FName& TypeName)
{
	GEngine->ForceGarbageCollection(true);

	if(const TWeakObjectPtr<UCY_Widget>* pWidget = ManagedWidgets.Find(TypeName))
	{
		const TWeakObjectPtr<UCY_Widget>& PreviousWidget = *pWidget;
		if(PreviousWidget.IsValid())
		{
			return PreviousWidget.Get();
		}
		ManagedWidgets.Remove(TypeName);
	}

	const TObjectPtr<UCY_Widget> Widget = Cast<UCY_Widget>(CreateWidget_Internal(TypeName, true));
	if(Widget == nullptr)
	{
		CY_CHECK(false);
		return nullptr;
	}

	AddExclusiveLayerWidget(Widget);
	
	ManagedWidgets.Emplace(TypeName, Widget);

	if(OnCreateWidget.IsBound())
	{
		OnCreateWidget.Broadcast(TypeName);
	}
	
	return Widget;
}

void UCY_WidgetManager::PreDestroyWidget(TObjectPtr<UCY_Widget> Widget)
{
	if(IsValid(Widget) == false)
	{
		return;
	}

	RemoveExclusiveLayerWidget(Widget);

	if(OnDestroyWidget.IsBound())
	{
		OnDestroyWidget.Broadcast(Widget->GetResourceWidgetInfo().GetWidgetName());
	}
}

bool UCY_WidgetManager::DestroyWidget(const FName& TypeName)
{
	const TObjectPtr<UCY_Widget> Widget = GetWidget(TypeName);
	if(Widget == nullptr)
	{
		return false;
	}

	PreDestroyWidget(Widget);
	Widget->FinishWidget();
	PostDestroyWidget(TypeName);	
	return true;
}

void UCY_WidgetManager::PostDestroyWidget(const FName& TypeName)
{
}

TObjectPtr<UCY_Widget> UCY_WidgetManager::GetWidget(const FName& TypeName)
{
	const TWeakObjectPtr<UCY_Widget>* pWidget = ManagedWidgets.Find(TypeName);
	if(pWidget && pWidget->IsValid())
	{
		return pWidget->Get();
	}

	return nullptr;
}

TObjectPtr<UCY_Widget> UCY_WidgetManager::CreateWidgetNotManaging(const FString& Path)
{
	return CreateWidget_Internal_NotManaging(Path);
}

TObjectPtr<UCY_Widget> UCY_WidgetManager::CreateWidgetNotManagingBySOP(const FSoftObjectPath& SoftObjectPath)
{
	const TObjectPtr<UCY_Widget> Widget = CreateWidgetNotManaging(SoftObjectPath.ToString());
	if(Widget == nullptr)
	{
		CY_CHECK(false);
		return nullptr;
	}
	
	return Widget;
}

TObjectPtr<UCY_Widget> UCY_WidgetManager::CreateWidget_Internal(const FName& TypeName, bool bManaged)
{
	const TObjectPtr<UCY_Mapper_Resource_Widget> ResourceWidgetMapper = Cast<UCY_Mapper_Resource_Widget>(gTableMng.GetTableMapper(ECY_TableDataType::Hero_Level));
	if(ResourceWidgetMapper == nullptr)
	{
		return nullptr;
	}

	const TObjectPtr<FResource_Widget> ResourceWidgetData = ResourceWidgetMapper->GetResourceWidgetData(TypeName);
	if(ResourceWidgetData == nullptr)
	{
		// 테이블 자료 문제
		return nullptr;
	}

	const FString ResourcePath = gTableMng.GetPath(ECY_TableDataType::Widget_Resource, ResourceWidgetData->Path_File, true);

	const TObjectPtr<UCY_Widget> ResultWidget = bManaged ? CreateWidget_Internal_Managing(ResourcePath) : CreateWidget_Internal_NotManaging(ResourcePath);

	if(ResultWidget == nullptr)
	{
		// 위젯 경로 에러?
		return nullptr;
	}

	FCY_ResourceWidgetInfo WidgetInfo;
	WidgetInfo.TypeName = ResourceWidgetData->TypeName;
	WidgetInfo.File = ResourcePath;
	WidgetInfo.zOrder = ResourceWidgetData->zOrder;
	WidgetInfo.ExclusiveGroup = static_cast<ECY_ExclusiveGroup>(ResourceWidgetData->ExclusiveGroup);
	WidgetInfo.NotRender3D = ResourceWidgetData->NotRender3D;

	ResultWidget->SetZOrder(WidgetInfo.zOrder);
	ResultWidget->SetResourceWidgetInfo(WidgetInfo);
	ResultWidget->InitWidget(TypeName, bManaged);

	return ResultWidget;
}

TObjectPtr<UCY_Widget> UCY_WidgetManager::CreateWidget_Internal_Managing(const FString& Path)
{
	static FString SubName = TEXT("Create Widget");
	const FString ClassPath = Path + TEXT("_C");
	
	const TObjectPtr<UCY_Widget> WidgetClass = Cast<UCY_Widget>(CY_Utility::LoadObjectFromFile(ClassPath, FCY_LoadResourceDelegate::CreateUObject(this, &UCY_WidgetManager::LoadComplete)));

	return WidgetClass;
}

TObjectPtr<UCY_Widget> UCY_WidgetManager::CreateWidget_Internal_NotManaging(const FString& Path) const
{
	static FString SubName = TEXT("Create Widget");
	const FString ClassPath = Path + TEXT("_C");
	
	const TObjectPtr<UClass> WidgetClass = Cast<UClass>(CY_Utility::LoadObjectFromFile(ClassPath));
	const TObjectPtr<UWorld> World = gInstance.GetWorld();
	
	if(World != nullptr && World->bIsTearingDown == false)
	{
		if(const TObjectPtr<UCY_Widget> Widget = CreateWidget<UCY_Widget>(World, WidgetClass))
		{
			Widget->Init();
			return Widget;
		}
	}
	
	return nullptr;
}

void UCY_WidgetManager::AddExclusiveLayerWidget(TObjectPtr<UCY_Widget> Widget)
{
	if(Widget == nullptr)
	{
		return;
	}

	const uint8 GroupIndex = static_cast<uint8>(Widget->GetResourceWidgetInfo().GetExclusiveGroup());
	if(GroupIndex != 0)
	{
		if(ExclusiveLayers.IsValidIndex(GroupIndex) && IsValid(ExclusiveLayers[GroupIndex]) && ExclusiveLayers[GroupIndex] != Widget)
		{
			const TObjectPtr<UCY_Widget> PreviousWidget = ExclusiveLayers[GroupIndex];
			if(IsValid(PreviousWidget))
			{
				DestroyWidget(PreviousWidget->GetResourceWidgetInfo().GetWidgetName());
			}
		}

		ExclusiveLayers[GroupIndex] = Widget;
	}
}

void UCY_WidgetManager::RemoveExclusiveLayerWidget(TObjectPtr<UCY_Widget> Widget)
{
	if(Widget == nullptr)
	{
		return;
	}

	const uint8 GroupIndex = static_cast<uint8>(Widget->GetResourceWidgetInfo().GetExclusiveGroup());

	if(GroupIndex != 0 && ExclusiveLayers.Num() > 0 && IsValid(ExclusiveLayers[GroupIndex]) && ExclusiveLayers[GroupIndex] != Widget)
	{
		ExclusiveLayers[GroupIndex] = nullptr;
	}
}

void UCY_WidgetManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> WidgetData)
{
	
}
