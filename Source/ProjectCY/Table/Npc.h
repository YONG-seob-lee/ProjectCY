#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Npc.generated.h"
    
USTRUCT()
struct FNpc: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Id = 0;
   UPROPERTY(EditAnywhere)
    int32 UnitId = 0;
   UPROPERTY(EditAnywhere)
    int32 BasePoint_Id = 0;
   UPROPERTY(EditAnywhere)
    FString Role_Type = FString();
   UPROPERTY(EditAnywhere)
    float Interaction_Radius;
};
