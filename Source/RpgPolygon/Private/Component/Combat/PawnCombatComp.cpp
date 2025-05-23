// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/PawnCombatComp.h"

#include "Component/Weapon/PawnWeaponComp.h"
#include "MotionWarpingComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "CoreTypes/PolyGameplayTags.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "SubSystem/ObjectPoolSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(PawnCombatCompLog, All, All);

void UPawnCombatComp::InitDependencies(UPawnWeaponComp* InPawnWeaponComp, UMotionWarpingComponent* InMotionWarpingComp)
{
	OwningPawnWeaponComp         = InPawnWeaponComp;
	OwningMotionWarpingComponent = InMotionWarpingComp;
	if (!OwningPawnWeaponComp.IsValid() || !OwningMotionWarpingComponent.IsValid())
	{
		UE_LOG(PawnCombatCompLog, Error, TEXT("%hs failed to initialize dependencies"), __FUNCTION__);
	}
}


UPawnWeaponComp* UPawnCombatComp::GetOwningPawnWeaponComp() const { return OwningPawnWeaponComp.Get(); }

UMotionWarpingComponent* UPawnCombatComp::GetOwningMotionWarpingComponent() const
{
	return OwningMotionWarpingComponent.Get();
}

bool UPawnCombatComp::IsValidBlock(const AActor* AttackActor) const
{
	FGameplayEventData Payload{};
	Payload.Instigator = GetOwner();
	Payload.Target     = AttackActor;

	// 判断是否为有效格挡
	const auto bIsValidBlock =
			UPolyFunctionLibrary::DoseActorHaveTag(GetOwner(), PolyGameplayTags::RpgPoly_Player_Status_Action_Blocking)
			&&
			UPolyFunctionLibrary::DirectionOpposite(AttackActor, GetOwner());

	return bIsValidBlock;
}

void UPawnCombatComp::BroadcastOnPreDeath() const { OnPreDeathDelegate.Broadcast(GetOwner()); }

UObjectPoolSubsystem* UPawnCombatComp::GetObjectPoolSubsystem()
{
	if (!GetWorld()) { return nullptr; }

	if (!ObjectPoolSubsystem.IsValid()) { ObjectPoolSubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>(); }
	return ObjectPoolSubsystem.Get();
}


void UPawnCombatComp::ShowFloatingDamageStr(const float Damage, bool bBlockedHit, bool bCriticalHit) {}

void UPawnCombatComp::SendCombatGameplayEvent(AActor*             Receive,
                                              const FGameplayTag& InEventTag,
                                              FGameplayEventData  Payload)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Receive, InEventTag, Payload);
}
