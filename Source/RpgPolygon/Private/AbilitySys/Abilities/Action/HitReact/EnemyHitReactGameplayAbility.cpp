// Garrett Gan All Right Reserved


#include "AbilitySys/Abilities/Action/HitReact/EnemyHitReactGameplayAbility.h"

#include "CoreTypes/PolyGameplayTags.h"

UEnemyHitReactGameplayAbility::UEnemyHitReactGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	FAbilityTriggerData Data{};
	Data.TriggerTag    = PolyGameplayTags::RpgPoly_Enemy_EventTag_Action_HitReact;
	Data.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Data);
}

UAnimMontage* UEnemyHitReactGameplayAbility::GetHitReactMontage(const FGameplayTag& HitReactTag)
{
	if (!HitReactTag.IsValid()){return nullptr;}
	const auto Montage = Montages.Find(HitReactTag);
	if (!Montage)
	{
		return nullptr;
	}
	
	return *Montage;
}
