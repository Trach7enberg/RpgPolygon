// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySys/Abilities/GameplayAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "Character/PolyCharacterBase.h"
#include "Component/Weapon/PawnWeaponComp.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "CoreTypes/PolyGameplayTags.h"
#include "Component/Combat/PawnCombatComp.h"
#include "Engine/AssetManager.h"

DEFINE_LOG_CATEGORY_STATIC(GameplayAbilityBase, All, All);

UGameplayAbilityBase::UGameplayAbilityBase() { AbilityActivationPolicy = EPolyAbilityActivationPolicy::OnTriggered; }

APolyCharacterBase* UGameplayAbilityBase::GetAvatarCharacter()
{
	OwningCharacter = Cast<APolyCharacterBase>(GetAvatarActorFromActorInfo());

	return OwningCharacter.Get();
}

AController* UGameplayAbilityBase::GetPawnController()
{
	if (!OwningPawnController.Get())
	{
		const auto Avatar    = GetAvatarCharacter();
		OwningPawnController = Avatar ? Avatar->GetController() : nullptr;
	}


	return OwningPawnController.Get();
}

UPawnCombatComp* UGameplayAbilityBase::GetPawnCombatComp()
{
	if (!GetAvatarActorFromActorInfo()) { return nullptr; }

	if (!OwningPawnCombatComp.IsValid())
	{
		OwningPawnCombatComp = GetAvatarActorFromActorInfo()->GetComponentByClass<UPawnCombatComp>();
	}
	return OwningPawnCombatComp.Get();
}

UPawnWeaponComp* UGameplayAbilityBase::GetPawnWeaponComp()
{
	if (!GetAvatarActorFromActorInfo()) { return nullptr; }

	if (!OwningPawnWeaponComp.IsValid())
	{
		OwningPawnWeaponComp = GetAvatarActorFromActorInfo()->GetComponentByClass<UPawnWeaponComp>();
	}
	return OwningPawnWeaponComp.Get();
}

UPolyAbilitySysComp* UGameplayAbilityBase::GetPolyAbilitySysComp()
{
	if (!GetAbilitySystemComponentFromActorInfo()) { return nullptr; }

	if (!OwningPolyAbilitySysComp.IsValid())
	{
		OwningPolyAbilitySysComp = GetAvatarActorFromActorInfo()->GetComponentByClass<UPolyAbilitySysComp>();
	}
	return OwningPolyAbilitySysComp.Get();
}

FGameplayEffectSpecHandle UGameplayAbilityBase::MakeDamageEffectSpecHandle(const TSubclassOf<UGameplayEffect>& GeClass,
                                                                           const FGameplayTag InCurrentAttackTypeTag,
                                                                           float InComboCount,
                                                                           float InWeaponBaseDamage)
{
	ensureMsgf(GeClass, TEXT("GameplayEffect Cant be Null"));
	if (!GeClass || !GetPolyAbilitySysComp() || !GetAvatarActorFromActorInfo()) { return {}; }

	auto ContextHandle = GetPolyAbilitySysComp()->MakeEffectContext();
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	auto EffectSpecHandle = GetPolyAbilitySysComp()->MakeOutgoingSpec(GeClass, GetAbilityLevel(), ContextHandle);

	// SetByCallerTag 供自定义计算时获取使用
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle,
	                                                              PolyGameplayTags::RpgPoly_Shared_SetByCaller_BaseDamage,
	                                                              InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle,
		                                                              InCurrentAttackTypeTag,
		                                                              InComboCount);
	}

	return EffectSpecHandle;
}

FActiveGameplayEffectHandle UGameplayAbilityBase::ApplyDamageEffectSpecToTarget(AActor* Target,
	const FGameplayEffectSpecHandle&                                                    InSpecHandle,
	EPolyConfirmType&                                                                   OutConfirm)
{
	const auto Asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!GetPolyAbilitySysComp() || !Asc || !InSpecHandle.IsValid())
	{
		OutConfirm = EPolyConfirmType::Failed;
		return {};
	}

	const auto ActiveEffectHandle = GetPolyAbilitySysComp()->
			ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, Asc);

	OutConfirm                                       = ActiveEffectHandle.WasSuccessfullyApplied()
		                                ? OutConfirm = EPolyConfirmType::Successful
		                                : OutConfirm = EPolyConfirmType::Failed;

	return ActiveEffectHandle;
}

void UGameplayAbilityBase::SetScalarParameterOnOwnerMeshMaterials(FName InParameterName, float InParameterValue) {}

UAnimMontage* UGameplayAbilityBase::GetRandomMontage(const TArray<UAnimMontage*>& InMontages) const
{
	ensure(!InMontages.IsEmpty());

	return InMontages.IsEmpty() ? nullptr : InMontages[FMath::RandRange(0, InMontages.Num() - 1)];
}

float UGameplayAbilityBase::GetWeaponBaseDamage()
{
	if (!GetPawnWeaponComp()) { return 0.f; }

	return GetPawnWeaponComp()->GetWeaponDataBaseDamage(GetAbilityLevel());
}

void UGameplayAbilityBase::Client_SpawnSystemAtLoc(TSoftObjectPtr<UNiagaraSystem> InNiagaraSystem, const FVector InLoc)
{
	if (!IsLocallyControlled()) { return; }
	UAssetManager::GetStreamableManager().RequestAsyncLoad(InNiagaraSystem.ToSoftObjectPath(),
	                                                       FStreamableDelegate::CreateLambda([InNiagaraSystem, this,
		                                                       InLoc]
	                                                       {
		                                                       const auto Ns = Cast<
			                                                       UNiagaraSystem>(InNiagaraSystem.Get());
		                                                       if (!Ns)
		                                                       {
			                                                       UE_LOG(GameplayAbilityBase,
			                                                              Warning,
			                                                              TEXT("%hs niagara system is null"),
			                                                              __FUNCTION__);
			                                                       return;
		                                                       }
		                                                       UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
			                                                       Ns,
			                                                       InLoc);
	                                                       }));
}

void UGameplayAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	switch (AbilityActivationPolicy)
	{
		case EPolyAbilityActivationPolicy::OnTriggered:
			break;
		case EPolyAbilityActivationPolicy::OnGiven:
			if (ActorInfo && !Spec.IsActive()) { ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle); }
			break;
	}
}

void UGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle     Handle,
                                      const FGameplayAbilityActorInfo*     ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      bool                                 bReplicateEndAbility,
                                      bool                                 bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	switch (AbilityActivationPolicy)
	{
		case EPolyAbilityActivationPolicy::OnTriggered:
			break;
		case EPolyAbilityActivationPolicy::OnGiven:
			if (ActorInfo && HasAuthority(&CurrentActivationInfo))
			{
				ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
			}
			break;
	}
}

UAnimMontage* UGameplayAbilityBase::GetCurrentAttackMontage() const
{
	// 子类重写
	return nullptr;
}
