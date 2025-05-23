// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/CharacterStartUp/DataAssetStartUp.h"
#include "DataAssetEnemyStartUp.generated.h"

class UEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UDataAssetEnemyStartUp : public UDataAssetStartUp
{
	GENERATED_BODY()

public:
	UDataAssetEnemyStartUp();

	/// 敌人的初始战斗能力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WarriorAbility")
	TArray<TSubclassOf<UEnemyGameplayAbility>> EnemyCombatAbilities{};
};
