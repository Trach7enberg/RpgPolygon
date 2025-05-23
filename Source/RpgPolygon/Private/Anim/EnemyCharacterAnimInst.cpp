// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/EnemyCharacterAnimInst.h"

#include "Character/KnightRunitEnemyCharacter.h"

AKnightRunitEnemyCharacter* UEnemyCharacterAnimInst::GetOwningEnemyCharacter()
{
	if (!KnightRunitEnemyCharacter.IsValid())
	{
		KnightRunitEnemyCharacter = Cast<AKnightRunitEnemyCharacter>(OwningCharacter);
	}
	return KnightRunitEnemyCharacter.Get();
}
