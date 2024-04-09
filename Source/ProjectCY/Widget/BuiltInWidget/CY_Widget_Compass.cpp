#include "CY_Widget_Compass.h"
#include "CommonUI/Public/AnalogSlider.h"
#include "Components/Image.h"

void UCY_Widget_Compass::Init()
{
}

void UCY_Widget_Compass::SetCompass(float AngleInDegrees) const
{
	// Default Degree = 0 Degree -> East
	// + Degree -> South -> West (양수)
	// - Degree -> North -> West (음수)

	// InValue Max = 1, Min = 0
	// 0 일 때 -180여아한다?
	// 1 일 때 180이어야 한다
	
	const float Value = AngleInDegrees / 360.f;
	//CY_LOG(TEXT("Compass InValue = %f"), Value );

	if(CPP_Compass)
	{
		if(const TObjectPtr<UMaterialInstanceDynamic> Material = CPP_Compass->GetDynamicMaterial())
		{
			TArray<FMaterialParameterInfo> ParameterInfos;
			TArray<FGuid> Guids;
			Material->GetAllScalarParameterInfo(ParameterInfos, Guids);
			Material->SetScalarParameterValueByInfo(ParameterInfos.Last(), Value);
		}
	}
}
