#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaEnemyCharacter.generated.h"

UCLASS()
class UNREALAIARENADEMO_API AArenaEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AArenaEnemyCharacter();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float AttackRange = 175.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float AttackCooldown = 1.25f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float AttackDamage = 15.f;
};
