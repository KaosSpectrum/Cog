#pragma once

#include "CoreMinimal.h"
#include "CogCommon.h"
#include "GameFramework/GameStateBase.h"
#include "CogSampleGameState.generated.h"

class UCogWindowManager;
class UCogEngineWindow_Selection;
class UCogSampleAbilitySystemComponent;

UCLASS()
class ACogSampleGameState : public AGameStateBase
{
    GENERATED_BODY()

    ACogSampleGameState(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void Tick(float DeltaSeconds) override;

private:

    //---------------------------------------------------------------------------------
    // To make sure it doesn't get garbage collected.
    //---------------------------------------------------------------------------------
    UPROPERTY()
    TObjectPtr<UObject> CogWindowManagerRef = nullptr;

    //---------------------------------------------------------------------------------
    // The game state has an AbilitySystemComponent to serve as the default instigator 
    // for effects that are not applied by characters.
    //---------------------------------------------------------------------------------
    UPROPERTY()
    UCogSampleAbilitySystemComponent* AbilitySystemComponent = nullptr;

#if ENABLE_COG

    void InitializeCog();

    void RegisterCommands();

    void UnregisterCommands();

    TObjectPtr<UCogWindowManager> CogWindowManager = nullptr;
    TObjectPtr<UCogEngineWindow_Selection> SelectionWindow = nullptr;

#endif //ENABLE_COG
};
