// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/CharacterAnimInstBase.h"
#include "EnemyCharacterAnimInst.generated.h"

class AKnightRunitEnemyCharacter;
/**
 * (骑士陨落)敌人动画蓝图基类
 */
UCLASS()
class RPGPOLYGON_API UEnemyCharacterAnimInst : public UCharacterAnimInstBase
{
	GENERATED_BODY()

public:
	/// 获取当前动画蓝图Owner的角色(玩家)
	UFUNCTION(BlueprintCallable, BlueprintPure,Category="PolyAnim")
	AKnightRunitEnemyCharacter* GetOwningEnemyCharacter();

protected:
	/// 当前蓝图owner,即玩家的实例
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TWeakObjectPtr<AKnightRunitEnemyCharacter> KnightRunitEnemyCharacter = nullptr;
};
