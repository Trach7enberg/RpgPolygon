// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySys/Abilities/EnemyGameplayAbility.h"
#include "EnemyOffensiveGameplayAbility.generated.h"


class UAnimMontage;

/**
 * 敌人基础攻击能力类
 */
UCLASS()
class RPGPOLYGON_API UEnemyOffensiveGameplayAbility : public UEnemyGameplayAbility
{
	GENERATED_BODY()

public:
	/// 攻击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAbility")
	TMap<int32, UAnimMontage*> AttackMontage{};

	virtual UAnimMontage* GetCurrentAttackMontage() const override;
};
