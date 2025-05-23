// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySys/Core/PolyAbilitySysComp.h"

#include "AbilitySys/Abilities/PolyGameplayAbility.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "SubSystem/PolyGiSubSystem.h"
#include "AbilitySys/Abilities/EnemyGameplayAbility.h"
#include "CoreTypes/PolyGameplayTags.h"


void UPolyAbilitySysComp::InitializeComponent()
{
	Super::InitializeComponent();
	if (!GetWorld() || !GetWorld()->GetGameInstance()) { return; }

	GiSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UPolyGiSubSystem>();
}

void UPolyAbilitySysComp::GiveInitialAbilities(TArray<TSubclassOf<UGameplayAbilityBase>>& InGameAbilitiesClass,
                                               bool                                       GrandAndActivateOnce,
                                               float                                      AbilityLevel)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (InGameAbilitiesClass.IsEmpty()) { return; }

	for (const auto& Ga : InGameAbilitiesClass) { GrantAbility(Ga, AbilityLevel, GrandAndActivateOnce); }
}

void UPolyAbilitySysComp::GiveInitialAbilities(
	TArray<TSubclassOf<UEnemyGameplayAbility>>& InEnemyGameAbilitiesClass,
	const float                                 AbilityLevel,
	const bool                                  GrandAndActivateOnce)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (InEnemyGameAbilitiesClass.IsEmpty()) { return; }

	for (const auto& Ga : InEnemyGameAbilitiesClass) { GrantAbility(Ga, AbilityLevel, GrandAndActivateOnce); }
}

void UPolyAbilitySysComp::GiveInitialAbilities(TArray<FPolyAbilityStruct>& InPolyAbilityStruct,
                                               bool                        GrandAndActivateOnce,
                                               const float                 AbilityLevel)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (InPolyAbilityStruct.IsEmpty()) { return; }

	for (const auto& GaPolyAbilityStruct : InPolyAbilityStruct)
	{
		if (!GaPolyAbilityStruct.Ability || !GaPolyAbilityStruct.IsValid()) { continue; }
		FGameplayAbilitySpec AbilitySpec(GaPolyAbilityStruct.Ability, AbilityLevel);
		AbilitySpec.SourceObject = GetAvatarActor();
		// 给GA 的容器 添加启动GA所对应的输入标签
		AbilitySpec.DynamicAbilityTags.AddTag(GaPolyAbilityStruct.InputTag);

		if (GrandAndActivateOnce) { GiveAbilityAndActivateOnce(AbilitySpec); }
		else { GiveAbility(AbilitySpec); }
	}
}


void UPolyAbilitySysComp::GiveInitialAbilities(const TArray<FPolyAbilityStruct>&   InPolyAbilityStruct,
                                               TArray<FGameplayAbilitySpecHandle>& OutSpecHandles,
                                               const float                         AbilityLevel)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (InPolyAbilityStruct.IsEmpty()) { return; }
	ClearAbilities(OutSpecHandles);
	OutSpecHandles.Empty();

	for (const auto& GaPolyAbilityStruct : InPolyAbilityStruct)
	{
		if (!GaPolyAbilityStruct.Ability || !GaPolyAbilityStruct.IsValid()) { continue; }
		FGameplayAbilitySpec AbilitySpec(GaPolyAbilityStruct.Ability, AbilityLevel);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.DynamicAbilityTags.AddTag(GaPolyAbilityStruct.InputTag);

		OutSpecHandles.Add(GiveAbility(AbilitySpec));
	}
}

void UPolyAbilitySysComp::ApplyInitialGameplayEffectToSelf(TArray<TSubclassOf<UGameplayEffect>> GameplayEffects,
                                                           const float                          AbilityLevel)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (GameplayEffects.IsEmpty()) { return; }

	for (const auto& Effect : GameplayEffects)
	{
		if (!Effect) { continue; }
		ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), AbilityLevel, MakeEffectContext());
	}
}

bool UPolyAbilitySysComp::TryActivateAbilityByTag(FGameplayTag AbilityTag)

{
	if (!AbilityTag.IsValid()) { return false; }
	return TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

void UPolyAbilitySysComp::GrantAbility(const TSubclassOf<UGameplayAbility> InAbility,
                                       const float                         AbilityLevel,
                                       const bool                          GrandAndActivateOnce)
{
	if (!InAbility) { return; }
	FGameplayAbilitySpec AbilitySpec(InAbility, AbilityLevel);
	AbilitySpec.SourceObject = GetAvatarActor();

	if (GrandAndActivateOnce) { GiveAbilityAndActivateOnce(AbilitySpec); }
	else { GiveAbility(AbilitySpec); }
}

FGameplayAbilitySpec* UPolyAbilitySysComp::GetAbilitySpecByInputTag(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) { return nullptr; }

	FScopedAbilityListLock AbilityListLock(*this);
	// 获取可以激活的能力数组
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive()) { return &AbilitySpec; }
	}
	return nullptr;
}

void UPolyAbilitySysComp::ClearAbilities(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	if (!IsOwnerActorAuthoritative()) { return; }
	if (InSpecHandles.IsEmpty()) { return; }
	FScopedAbilityListLock AbilityListLock(*this);
	for (const auto& SpecHandle : InSpecHandles)
	{
		CancelAbilityHandle(SpecHandle);
		ClearAbility(SpecHandle);
	}
}

void UPolyAbilitySysComp::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) { return; }

	FScopedAbilityListLock ScopedAbilityListLock(*this);
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) { continue; }

		// TODO 应该由互动组件处理逻辑 
		// 单点自动行走,输入多点击的情况下会选择最后的行走路径
		if (InInputTag == PolyGameplayTags::RpgPoly_InputTag_Click_Environment)
		{
			if (AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
				TryActivateAbility(AbilitySpec.Handle);
			}
			else { TryActivateAbility(AbilitySpec.Handle); }
			continue;
		}

		// 如果是锁定目标技能,限制为按键切换模式,即按下开启再按下就关闭
		if (InInputTag == PolyGameplayTags::RpgPoly_InputTag_TargetLock)
		{
			if (AbilitySpec.IsActive()) { CancelAbilityHandle(AbilitySpec.Handle); }
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
				AbilitySpecInputPressed(AbilitySpec);
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed,
				                      AbilitySpec.Handle,
				                      AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
			continue;
		}
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UPolyAbilitySysComp::OnAbilityInputRelease(const FGameplayTag& InInputTag)
{
	if (InInputTag == PolyGameplayTags::RpgPoly_InputTag_Block)
	{
		const auto InAbilitySpec = GetAbilitySpecByInputTag(InInputTag);
		if (!InAbilitySpec) { return; }
		AbilitySpecInputReleased(*InAbilitySpec);
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,
		                      InAbilitySpec->Handle,
		                      InAbilitySpec->ActivationInfo.GetActivationPredictionKey());
	}
}
