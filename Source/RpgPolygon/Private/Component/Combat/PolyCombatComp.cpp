// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/PolyCombatComp.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "MotionWarpingComponent.h"
#include "Component/Weapon/PawnWeaponComp.h"
#include "Component/Weapon/PolyWeaponComp.h"
#include "CoreTypes/PolyGameplayTags.h"

void UPolyCombatComp::InitDependencies(UPawnWeaponComp* InPawnWeaponComp, UMotionWarpingComponent* InMotionWarpingComp)
{
	Super::InitDependencies(InPawnWeaponComp, InMotionWarpingComp);

	OwningPolyWeaponComp = Cast<UPolyWeaponComp>(GetOwningPawnWeaponComp());
}

void UPolyCombatComp::EnableWeaponCombatDetect(bool bShouldEnable)
{
	if (!GetOwningPolyWeaponComp()) { return; }
	GetOwningPolyWeaponComp()->EnableWeaponCollision(bShouldEnable);
}

FOnPreDeathSignature& UPolyCombatComp::GetCharacterPreOnDeathDelegate() { return OnPreDeathDelegate; }

FVector UPolyCombatComp::GetCombatSocketLocationByTag(FGameplayTag InSocketTypeTag)
{
	if (!GetOwningPolyWeaponComp()) { return {}; }

	return GetOwningPolyWeaponComp()->GetWeaponSocketLocationByTag(InSocketTypeTag);
}

void UPolyCombatComp::UpdateMotionWarpingTarget(FTransform InTrans, FName WarpTargetName)
{
	if (!GetOwningMotionWarpingComponent()) { return; }

	GetOwningMotionWarpingComponent()->AddOrUpdateWarpTargetFromTransform(WarpTargetName, InTrans);
}

void UPolyCombatComp::ShowFloatingDamageText(const float Damage, bool bBlockedHit, bool bCriticalHit) {}

void UPolyCombatComp::ExecuteHitReact(AActor* Instigator)
{
	if (!Instigator || !GetOwner()) { return; }
	FGameplayEventData Payload{};
	Payload.Instigator = Instigator;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),
	                                                         PolyGameplayTags::RpgPoly_Player_EventTag_Action_HitReact,
	                                                         Payload);
}
