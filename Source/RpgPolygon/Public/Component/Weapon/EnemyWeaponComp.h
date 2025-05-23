// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Weapon/PawnWeaponComp.h"
#include "EnemyWeaponComp.generated.h"

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UEnemyWeaponComp : public UPawnWeaponComp
{
	GENERATED_BODY()

private:
	virtual void OnWeaponBeginHit(AActor* HitActor, const FHitResult* HitResult) override;
	virtual void OnWeaponEndHit(AActor* HitActor, const FHitResult* HitResult) override;
};
