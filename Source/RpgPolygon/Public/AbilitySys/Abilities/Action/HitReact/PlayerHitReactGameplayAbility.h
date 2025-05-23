// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySys/Abilities/PolyGameplayAbility.h"
#include "PlayerHitReactGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPlayerHitReactGameplayAbility : public UPolyGameplayAbility
{
	GENERATED_BODY()

public:
	UPlayerHitReactGameplayAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAbility|Player")
	TMap<FGameplayTag, UAnimMontage*> Montages{};

	UFUNCTION(BlueprintCallable, Category="PolyAbility|Player")
	UAnimMontage* GetHitReactMontage(UPARAM(ref) const FGameplayTag& HitReactTag);
};
