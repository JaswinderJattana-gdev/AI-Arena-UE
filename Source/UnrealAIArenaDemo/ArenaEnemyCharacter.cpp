#include "ArenaEnemyCharacter.h"
#include "ArenaEnemyAIController.h"

AArenaEnemyCharacter::AArenaEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AArenaEnemyAIController::StaticClass();
}

void AArenaEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Enemy BeginPlay: %s"), *GetName());
}
