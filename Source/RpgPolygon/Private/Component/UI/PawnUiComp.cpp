// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/PawnUiComp.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "Character/PolyCharacterBase.h"

void UPawnUiComp::InitialUiComponent()
{
	// 子类应该实现
}

UPolyAbilitySysComp* UPawnUiComp::GetPolyAbilitySysComp()
{
	if (!PolyAsc.IsValid())
	{
		PolyAsc = Cast<UPolyAbilitySysComp>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()));
	}
	return PolyAsc.Get();
}

APolyCharacterBase* UPawnUiComp::GetOwnerCharacter()
{
	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<APolyCharacterBase>(GetOwningPawn());
	}
	return OwnerCharacter.Get();
}
