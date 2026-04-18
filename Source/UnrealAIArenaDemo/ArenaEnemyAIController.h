#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "ArenaEnemyAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;

UCLASS()
class UNREALAIARENADEMO_API AArenaEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AArenaEnemyAIController();

protected:
    virtual void OnPossess(APawn* InPawn) override;

    UFUNCTION()
    void HandleTargetPerception(AActor* Actor, FAIStimulus Stimulus);

public:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* PerceptionComp;

    UPROPERTY()
    UAISenseConfig_Sight* SightConfig;

    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bDebugPerceptionLogs = true;

    // Blackboard key names 
    static const FName BB_TargetActor;
    static const FName BB_LastKnownLocation;
    static const FName BB_HasLOS;
private:
    // If perception fires before BB is ready, cache the latest event
    TWeakObjectPtr<AActor> PendingPerceptionActor;
    FAIStimulus PendingPerceptionStimulus;
    bool bHasPendingPerception = false;

    void ApplyPerceptionToBlackboard(AActor* Actor, const FAIStimulus& Stimulus);
    void TryConsumePendingPerception();

};
