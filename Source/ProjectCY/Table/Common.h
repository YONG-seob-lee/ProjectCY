#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Common.generated.h"
    
USTRUCT()
struct FCommon: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Id = 0;
   UPROPERTY(EditAnywhere)
    FString Contents_Type = FString();
   UPROPERTY(EditAnywhere)
    FString Contents = FString();
   UPROPERTY(EditAnywhere)
    int32 Param01 = 0;
   UPROPERTY(EditAnywhere)
    int32 Param02 = 0;
   UPROPERTY(EditAnywhere)
    float Param03;
   UPROPERTY(EditAnywhere)
    float Param04;
};
