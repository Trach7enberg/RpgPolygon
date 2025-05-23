// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySys/Core/PolyAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "AbilitySys/Core/PolyAbilitySystemGlobals.h"
#include "Interface/CombatInterface.h"
#include "Interface/Provider/CombatProvider.h"
#include "Net/UnrealNetwork.h"


#pragma region RepFunc
void UPolyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// 注册health变量用于复制,这是复制任何变量所需的步骤
	// 复制条件 COND_None ,也就是没有条件的复制
	// REPNOTIFY_Always 意味着如果在服务器上设置了值,就复制给客户端,那个值将被更新和设置,这里的值就是我们的CurrentHealth
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, CurrentMana, COND_None, REPNOTIFY_Always);

	// 主要属性
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	// 次要属性
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, LightingResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPolyAttributeSet, ArcaneResistance, COND_None, REPNOTIFY_Always);
}


void UPolyAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldValue) const
{
	// 通知GAS currentHealth刚刚被复制了,使GAS整个系统协调工作,让能力系统记录这一变化并保存旧值的跟踪,以防止需要回滚
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, CurrentHealth, OldValue);
}

void UPolyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, MaxHealth, OldValue);
}

void UPolyAttributeSet::OnRep_CurrentMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, CurrentMana, OldValue);
}

void UPolyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, MaxMana, OldValue);
}

void UPolyAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, Strength, OldValue);
}

void UPolyAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, Intelligence, OldValue);
}

void UPolyAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, Resilience, OldValue);
}

void UPolyAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, Vigor, OldValue);
}

void UPolyAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, Armor, OldValue);
}

void UPolyAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, ArmorPenetration, OldValue);
}

void UPolyAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, BlockChance, OldValue);
}

void UPolyAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, CriticalHitChance, OldValue);
}

void UPolyAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, CriticalHitResistance, OldValue);
}

void UPolyAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, CriticalHitDamage, OldValue);
}

void UPolyAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, HealthRegeneration, OldValue);
}

void UPolyAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, ManaRegeneration, OldValue);
}

void UPolyAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, FireResistance, OldValue);
}

void UPolyAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, PhysicalResistance, OldValue);
}

void UPolyAttributeSet::OnRep_LightingResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, LightingResistance, OldValue);
}

void UPolyAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPolyAttributeSet, ArcaneResistance, OldValue);
}

#pragma endregion

void UPolyAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UPolyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (!GetOwningAbilitySystemComponent()) { return; }

	auto       TmpGeContext = Data.EffectSpec.GetContext();
	const auto GeContext    = UPolyAbilitySystemGlobals::GetCustomGeContext(TmpGeContext.Get());

	// 当前As的拥有者受伤了
	if (Data.EvaluatedData.Attribute == GetInComingDamageAttribute() && GetInComingDamage() != 0.f)
	{
		if (FMath::IsNearlyEqual(GetCurrentHealth(), 0.f))
		{
			//TODO Death
			return;
		}

		const auto Instigator       = GeContext->GetEffectCauser();
		const auto Suffer           = GetOwningAbilitySystemComponent()->GetAvatarActor();
		const auto InCombatProvider = Cast<ICombatProvider>(Suffer);
		const auto OldHealth        = GetCurrentHealth();
		const auto DamageDone       = GetInComingDamage();
		const auto NewHealth        = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
		SetInComingDamage(0);

		if (!InCombatProvider) { return; }
		if (!InCombatProvider->GetCombatInterface()) { return; }
		InCombatProvider->GetCombatInterface()->ShowFloatingDamageText(DamageDone);
		InCombatProvider->GetCombatInterface()->ExecuteHitReact(Instigator);
	}
}


UPolyAbilitySysComp* UPolyAttributeSet::GetMyCurrentAbilitySystem()
{
	if (!CurrentPolyAbilitySystem)
	{
		// 存储我们自己的ASC组件 方便后面使用
		CurrentPolyAbilitySystem = Cast<UPolyAbilitySysComp>(
		                                                     GetOwningAbilitySystemComponent());
	}
	return CurrentPolyAbilitySystem.Get();
}
