#pragma once

#include "CoreMinimal.h"
#include "CogWindow.h"
#include "CogEngineWindow_Collisions.generated.h"

class UCogEngineDataAsset_Collisions;

UCLASS(Config = Cog)
class COGENGINE_API UCogEngineWindow_Collisions : public UCogWindow
{
    GENERATED_BODY()

public:

    UCogEngineWindow_Collisions();

    void SetCollisionsAsset(const UCogEngineDataAsset_Collisions* Asset);

private:

    virtual void RenderHelp() override;

    virtual void RenderContent() override;

    struct FChannel
    {
        bool IsValid = false;
        FColor Color;
    };

    TWeakObjectPtr<UCogEngineDataAsset_Collisions> CollisionsAsset;

    FChannel Channels[ECC_MAX];

    UPROPERTY(Config)
    int32 ObjectTypesToQuery = 0;

    UPROPERTY(Config)
    int32 ProfileIndex = 0;

    UPROPERTY(Config)
    int QueryType = 0;
    
    UPROPERTY(Config)
    float QueryDistance = 5000.0f;
    
    UPROPERTY(Config)
    float QueryThickness = 0.0f;
    
    UPROPERTY(Config)
    bool UseComplexCollisions = false;
    
    UPROPERTY(Config)
    bool ShowActorsNames = false;

    UPROPERTY(Config)
    bool ShowQuery = false;
};
