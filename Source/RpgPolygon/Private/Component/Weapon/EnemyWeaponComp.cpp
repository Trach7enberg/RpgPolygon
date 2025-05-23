// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/EnemyWeaponComp.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "Component/Combat/PawnCombatComp.h"
#include "CoreTypes/PolyGameplayTags.h"

DEFINE_LOG_CATEGORY_STATIC(EnemyWeaponCompLog, All, All);

void UEnemyWeaponComp::OnWeaponBeginHit(AActor* HitActor, const FHitResult* HitResult)
{
	if (!GetOwningCombatComp()) { return; }

	OverlappedActors.AddUnique(HitActor);

	// 判断目标(HitActor=Suffer)是否在翻滚中
	// if (UPolyFunctionLibrary::DoseActorHaveTag(HitActor, PolyGameplayTags::RpgPoly_Player_Status_Rolling)) { return; }

	// 判断是否为有效格挡
	// if (IsValidBlock(HitActor))
	// {
	// 	// 给Suffer发送SuccessfulBlock事件
	// 	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor,
	// 															 PolyGameplayTags::RpgPoly_Player_EventTag_SuccessfulBlock,
	// 															 Payload);
	// 	return;
	// }

	FGameplayEventData Payload{};
	Payload.Instigator = GetOwner();
	Payload.Target     = HitActor;
	// 发送Enemy_MeleeHit事件
	GetOwningCombatComp()->SendCombatGameplayEvent(GetOwner(),
	                                               PolyGameplayTags::RpgPoly_Enemy_EventTag_Offensive_MeleeHit,
	                                               Payload);
	
}

void UEnemyWeaponComp::OnWeaponEndHit(AActor* HitActor, const FHitResult* HitResult) {}
