// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySys/Core/PawnAttributeSet.h"

#include "Component/Combat/PawnCombatComp.h"


UPawnCombatComp* UPawnAttributeSet::GetOwningCombatComp()
{
	if (const auto OwnerAsc = GetOwningAbilitySystemComponent())
	{
		if (const auto Owner = OwnerAsc->GetAvatarActor())
		{
			OwningCombatComp = Owner->FindComponentByClass<UPawnCombatComp>();
		}
	}
	return OwningCombatComp.Get();
}
