#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Camera.generated.h"
    
USTRUCT()
struct FCamera: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Id = 0;
   UPROPERTY(EditAnywhere)
    FString Camera_Type = FString();
   UPROPERTY(EditAnywhere)
    FString Camera_Sub_Type = FString();
};
