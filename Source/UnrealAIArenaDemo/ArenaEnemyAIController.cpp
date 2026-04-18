#include "ArenaEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

const FName AArenaEnemyAIController::BB_TargetActor(TEXT("TargetActor"));
const FName AArenaEnemyAIController::BB_LastKnownLocation(TEXT("LastKnownLocation"));
const FName AArenaEnemyAIController::BB_HasLOS(TEXT("HasLOS"));

AArenaEnemyAIController::AArenaEnemyAIController()
{
    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
    SetPerceptionComponent(*PerceptionComp);

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 8000.f;
    SightConfig->LoseSightRadius = 8000.f;
    SightConfig->PeripheralVisionAngleDegrees = 140.f;
    SightConfig->SetMaxAge(10.0f);

    // detect all affiliations
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    PerceptionComp->ConfigureSense(*SightConfig);
    PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

    PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(
        this, &AArenaEnemyAIController::HandleTargetPerception
    );
    UE_LOG(LogTemp, Warning, TEXT("Perception delegate bound"));
}

void AArenaEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    UE_LOG(LogTemp, Warning, TEXT("AIController OnPossess: %s"), *GetName());

    UE_LOG(LogTemp, Warning, TEXT("OnPossess: BehaviorTreeAsset = %s"),
        BehaviorTreeAsset ? *BehaviorTreeAsset->GetName() : TEXT("NULL"));

    // Init BB/BT FIRST
    if (BehaviorTreeAsset)
    {
        UBlackboardComponent* BBComp = nullptr;
        UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BBComp);
        UE_LOG(LogTemp, Warning, TEXT("UseBlackboard returned BBComp = %s"),
            BBComp ? TEXT("VALID") : TEXT("NULL"));

        RunBehaviorTree(BehaviorTreeAsset);
        UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree called. GetBlackboardComponent() = %s"),
            GetBlackboardComponent() ? TEXT("VALID") : TEXT("NULL"));

        UE_LOG(LogTemp, Warning, TEXT("Behavior Tree started."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BehaviorTreeAsset is NULL (set it in BP_ArenaEnemyAIController)."));
    }

    // update perception listener
    if (PerceptionComp)
    {
        PerceptionComp->RequestStimuliListenerUpdate();
        UE_LOG(LogTemp, Warning, TEXT("Requested Stimuli Listener Update"));
    }

    // Apply any cached perception that happened early
    TryConsumePendingPerception();
}

void AArenaEnemyAIController::HandleTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor) return;

    if (bDebugPerceptionLogs)
    {
        UE_LOG(LogTemp, Warning, TEXT("Perception Event: Actor=%s | Sensed=%s | HasTag(Player)=%s | StimLoc=%s"),
            *Actor->GetName(),
            Stimulus.WasSuccessfullySensed() ? TEXT("YES") : TEXT("NO"),
            Actor->ActorHasTag(TEXT("Player")) ? TEXT("YES") : TEXT("NO"),
            *Stimulus.StimulusLocation.ToString());
    }

    if (!Actor->ActorHasTag(TEXT("Player")))
    {
        return;
    }

    // If BB isn't ready yet, cache and apply later
    if (!GetBlackboardComponent())
    {
        PendingPerceptionActor = Actor;
        PendingPerceptionStimulus = Stimulus;
        bHasPendingPerception = true;

        if (bDebugPerceptionLogs)
        {
            UE_LOG(LogTemp, Warning, TEXT("Blackboard not ready. Cached perception event."));
            return;
        }
    }

    ApplyPerceptionToBlackboard(Actor, Stimulus);
}
void AArenaEnemyAIController::ApplyPerceptionToBlackboard(AActor* Actor, const FAIStimulus& Stimulus)
{
    UBlackboardComponent* BB = GetBlackboardComponent();
    if (!BB || !Actor) return;

    if (Stimulus.WasSuccessfullySensed())
    {
        BB->SetValueAsObject(BB_TargetActor, Actor);
        BB->SetValueAsBool(BB_HasLOS, true);
        BB->SetValueAsVector(BB_LastKnownLocation, Actor->GetActorLocation());
        UE_LOG(LogTemp, Warning, TEXT("BB Updated: SEEN"));
    }
    else
    {
        BB->SetValueAsBool(BB_HasLOS, false);
        BB->SetValueAsVector(BB_LastKnownLocation, Stimulus.StimulusLocation);
        UE_LOG(LogTemp, Warning, TEXT("BB Updated: LOST"));
    }
}

void AArenaEnemyAIController::TryConsumePendingPerception()
{
    if (!bHasPendingPerception) return;
    if (!GetBlackboardComponent()) return;
    if (!PendingPerceptionActor.IsValid()) return;

    UE_LOG(LogTemp, Warning, TEXT("Consuming cached perception event."));
    ApplyPerceptionToBlackboard(PendingPerceptionActor.Get(), PendingPerceptionStimulus);

    bHasPendingPerception = false;
    PendingPerceptionActor.Reset();
}
