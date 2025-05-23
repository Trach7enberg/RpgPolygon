// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PawnAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class UPawnCombatComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPawnAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPawnCombatComp* GetOwningCombatComp() ;

private:
	UPROPERTY()
	TWeakObjectPtr<UPawnCombatComp> OwningCombatComp;
};
