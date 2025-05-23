// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/PolyCharacterAnimInst.h"

#include "Character/PolyCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(PolyCharacterAnimInstLog, All, All);

void UPolyCharacterAnimInst::NativeInitializeAnimation() { Super::NativeInitializeAnimation(); }

APolyCharacter* UPolyCharacterAnimInst::GetOwningPolyCharacter()
{
	if (!OwningPolyCharacter.IsValid()) { OwningPolyCharacter = Cast<APolyCharacter>(OwningCharacter); }
	return OwningPolyCharacter.Get();
}
