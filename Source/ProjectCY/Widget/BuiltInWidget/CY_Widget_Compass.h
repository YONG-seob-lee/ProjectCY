

#pragma once

#include "CoreMinimal.h"
#include "CY_Widget.h"
#include "CY_Widget_Compass.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCY_API UCY_Widget_Compass : public UCY_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/Widget/BuiltInWidget/CompassWidget.CompassWidget")); }

	void Init();

	void SetCompass(float AngleInDegrees) const;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Compass = nullptr;
};
