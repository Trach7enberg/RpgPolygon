// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/PawnWeaponComp.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Component/Combat/PawnCombatComp.h"
#include "Item/Weapon/PolyWeaponBase.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(PawnWeaponCompLog, All, All);

UPawnWeaponComp::UPawnWeaponComp() {}

void UPawnWeaponComp::InitializePawnComponent()
{
}

UPawnCombatComp* UPawnWeaponComp::GetOwningCombatComp()
{
	if (!OwningCombatComp.IsValid())
	{
		if (!GetOwner())
		{
			UE_LOG(PawnWeaponCompLog, Warning, TEXT("failed to get owner component"));
			return nullptr;
		}
		OwningCombatComp = GetOwner()->FindComponentByClass<UPawnCombatComp>();
	}
	return OwningCombatComp.Get();
}

void UPawnWeaponComp::RegisterSpawnedWeapon(const FGameplayTag& InGt,
                                            APolyWeaponBase*    InWeapon,
                                            bool                RegisterAndEquippedNow)
{
	ensureMsgf(InWeapon && InGt.IsValid(), TEXT("Weapon is null"));
	if (!InWeapon) { return; }
	WeaponArrays.AddUnique({InGt, InWeapon});

	// TODO 解除武器需要取消绑定?
	if (!InWeapon->OnWeaponBeginOverlapDelegate.IsBoundToObject(this))
	{
		InWeapon->OnWeaponBeginOverlapDelegate.BindUObject(this, &ThisClass::OnWeaponBeginHit);
	}
	if (!InWeapon->OnWeaponEndOverlapDelegate.IsBoundToObject(this))
	{
		InWeapon->OnWeaponEndOverlapDelegate.BindUObject(this, &ThisClass::OnWeaponEndHit);
	}

	if (RegisterAndEquippedNow)
	{
		SetCurrentWeaponTag(InGt);
	}
}

APolyWeaponBase* UPawnWeaponComp::GetWeaponByTag(const FGameplayTag& InGt)
{
	if (!InGt.IsValid())
	{
		UE_LOG(PawnWeaponCompLog, Log, TEXT("WeaponTag Invalid!"));
		return nullptr;
	}

	// if (const auto Weapon = WeaponMap.Find(InGt)) { return *Weapon; }

	for (const auto& WeaponMapping : WeaponArrays)
	{
		if (!WeaponMapping.WeaponTag.IsValid()) { continue; }
		if (WeaponMapping.WeaponTag == InGt) { return WeaponMapping.Weapon; }
	}

	return nullptr;
}


APolyWeaponBase* UPawnWeaponComp::GetCurrentWeapon()
{
	return GetWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnWeaponComp::EnableWeaponCollision(bool bShouldEnable, EEquippedState EquippedState)
{
	if (!GetOwner() && !GetOwner()->HasAuthority()) { return; }

	if (EquippedState == EEquippedState::Current)
	{
		const auto Weapon = GetCurrentWeapon();
		if (!Weapon) { return; }
		Weapon->EnableCollision(bShouldEnable);
		if (!bShouldEnable) { OverlappedActors.Empty(); }
	}
}

float UPawnWeaponComp::GetWeaponDataBaseDamage(float InAbilityLevel)
{
	const auto InWeapon = GetCurrentWeapon();
	if (!InWeapon) { return 0.f; }

	return InWeapon->GetWeaponDataBaseDamage(InAbilityLevel);
}

void UPawnWeaponComp::DestroyWeapon()
{
	for (const auto& WeaponMapping : WeaponArrays)
	{
		if (WeaponMapping.Weapon) { WeaponMapping.Weapon->DestroyWeapon(); }
	}
}

void UPawnWeaponComp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPawnWeaponComp, WeaponArrays);
	DOREPLIFETIME(UPawnWeaponComp, CurrentEquippedWeaponTag);
}

void UPawnWeaponComp::OnWeaponBeginHit(AActor* HitActor, const FHitResult* HitResult)
{
	// 子类实现
}

void UPawnWeaponComp::OnWeaponEndHit(AActor* HitActor, const FHitResult* HitResult)
{
	// 子类实现
}

void UPawnWeaponComp::OnRep_WeaponArrays() {}

void UPawnWeaponComp::OnRep_CurrentEquippedWeaponTag(FGameplayTag OldValue)
{
}

float UPawnWeaponComp::GetCurrentEquippedWeaponDamage(float InLevel)
{
	const auto Weapon = GetCurrentWeapon();

	return (Weapon) ? Weapon->GetWeaponDataBaseDamage(InLevel) : 0.f;
}

FVector UPawnWeaponComp::GetWeaponSocketLocationByTag(const FGameplayTag& InSocketType)
{
	const auto InWeapon = GetCurrentWeapon();
	return (InWeapon) ? InWeapon->GetWeaponSocketLocByTag(InSocketType) : FVector::Zero();
}
