#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Npc_Contents.generated.h"
    
USTRUCT()
struct FNpc_Contents: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Id = 0;
   UPROPERTY(EditAnywhere)
    int32 UnitId = 0;
   UPROPERTY(EditAnywhere)
    int32 ImageType = 0;
   UPROPERTY(EditAnywhere)
    FString ContentName = FString();
};
