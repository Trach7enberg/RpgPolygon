// Garrett Gan All Right Reserved


#include "AbilitySys/Abilities/Action/HitReact/PlayerHitReactGameplayAbility.h"

#include "CoreTypes/PolyGameplayTags.h"

UPlayerHitReactGameplayAbility::UPlayerHitReactGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	FAbilityTriggerData Data{};
	Data.TriggerTag    = PolyGameplayTags::RpgPoly_Player_EventTag_Action_HitReact;
	Data.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Data);
}

UAnimMontage* UPlayerHitReactGameplayAbility::GetHitReactMontage(const FGameplayTag& HitReactTag)
{
	if (!HitReactTag.IsValid()) { return nullptr; }
	const auto Montage = Montages.Find(HitReactTag);
	if (!Montage) { return nullptr; }

	return *Montage;
}
