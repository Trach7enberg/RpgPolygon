// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySys/Abilities/GameplayAbilityBase.h"
#include "PolyGameplayAbility.generated.h"

class UPolyWeaponComp;
class UPolyCombatComp;
class APolyController;
class APolyCharacter;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPolyGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	APolyCharacter* GetPolyCharacter();

	/// 获取玩家化身角色
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	APolyController* GetPolyController();

	/// 获取玩家化身的战斗组件
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	UPolyCombatComp* GetPolyCombatComp();

	/// 获取玩家化身的武器组件
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	UPolyWeaponComp* GetPolyWeaponComp();

	/// 检测追踪获取玩家控制器鼠标下的HitResult
	/// @param OutHitResult
	/// @param CollisionChannel
	UFUNCTION(BlueprintCallable, Category="PolyAbility")
	void GetHitResultUnderCursor(FHitResult& OutHitResult,ECollisionChannel CollisionChannel = ECC_Visibility);

private:
	// 只持有对象引用不会增加计数
	TWeakObjectPtr<APolyCharacter>  CurrentPolyCharacter  = nullptr;
	TWeakObjectPtr<APolyController> CurrentPolyController = nullptr;
	TWeakObjectPtr<UPolyCombatComp> CurrentPolyCombatComp = nullptr;
	TWeakObjectPtr<UPolyWeaponComp> CurrentPolyWeaponComp = nullptr;
};
