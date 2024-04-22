#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Hud_TopExpander.generated.h"
    
USTRUCT()
struct FHud_TopExpander: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 id = 0;
   UPROPERTY(EditAnywhere)
    int32 Image_Path = 0;
   UPROPERTY(EditAnywhere)
    FString Expander_Type = FString();
};
