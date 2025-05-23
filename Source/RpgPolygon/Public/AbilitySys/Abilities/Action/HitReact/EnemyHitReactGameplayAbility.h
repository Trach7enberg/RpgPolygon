// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySys/Abilities/EnemyGameplayAbility.h"
#include "EnemyHitReactGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UEnemyHitReactGameplayAbility : public UEnemyGameplayAbility
{
	GENERATED_BODY()

public:
	UEnemyHitReactGameplayAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAbility")
	TMap<FGameplayTag, UAnimMontage*> Montages{};

	UFUNCTION(BlueprintCallable, Category="PolyAbility")
	UAnimMontage* GetHitReactMontage(UPARAM(ref) const FGameplayTag& HitReactTag);
};
