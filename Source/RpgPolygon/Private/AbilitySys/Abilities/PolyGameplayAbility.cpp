// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySys/Abilities/PolyGameplayAbility.h"

#include "Character/PolyCharacter.h"
#include "Component/Combat/PolyCombatComp.h"
#include "Component/Weapon/PolyWeaponComp.h"
#include "Controller/Player/PolyController.h"

APolyCharacter* UPolyGameplayAbility::GetPolyCharacter()
{
	if (!CurrentPolyCharacter.IsValid()) { CurrentPolyCharacter = Cast<APolyCharacter>(GetAvatarActorFromActorInfo()); }
	return (CurrentPolyCharacter.IsValid()) ? CurrentPolyCharacter.Get() : nullptr;
}

APolyController* UPolyGameplayAbility::GetPolyController()
{
	if (!GetCurrentActorInfo()) { return nullptr; }

	if (!CurrentPolyController.IsValid())
	{
		CurrentPolyController = Cast<APolyController>(GetCurrentActorInfo()->PlayerController);
	}
	return (CurrentPolyController.IsValid()) ? CurrentPolyController.Get() : nullptr;
}

UPolyCombatComp* UPolyGameplayAbility::GetPolyCombatComp()
{
	if (!GetPolyCharacter()) { return nullptr; }
	if (!GetPawnCombatComp()) { return nullptr; }

	if (!CurrentPolyCombatComp.IsValid()) { CurrentPolyCombatComp = Cast<UPolyCombatComp>(GetPawnCombatComp()); }

	return CurrentPolyCombatComp.Get();
}

UPolyWeaponComp* UPolyGameplayAbility::GetPolyWeaponComp()
{
	if (!GetPolyCharacter()) { return nullptr; }
	if (!GetPawnWeaponComp()) { return nullptr; }

	if (!CurrentPolyWeaponComp.IsValid()) { CurrentPolyWeaponComp = Cast<UPolyWeaponComp>(GetPawnWeaponComp()); }

	return CurrentPolyWeaponComp.Get();
}

void UPolyGameplayAbility::GetHitResultUnderCursor(FHitResult& OutHitResult, ECollisionChannel CollisionChannel)
{
	if (!GetPolyController()) { return; }
	GetPolyController()->GetHitResultUnderCursor(CollisionChannel, false, OutHitResult);
}
