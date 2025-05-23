// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

struct FGenericTeamId;

UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 战斗接口
 */
class RPGPOLYGON_API ICombatInterface
{
	GENERATED_BODY()

public:
	/// 只在服务器端进行检测,开启战斗武器检测Overlap
	/// @param bShouldEnable 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void EnableWeaponCombatDetect(bool bShouldEnable) = 0;

	/// 获取玩家准备死亡时的委托(播放死亡动画时)
	/// @return 
	virtual FOnPreDeathSignature& GetCharacterPreOnDeathDelegate() = 0;

	/// 获取当前战斗插槽位置
	/// @param InSocketTypeTag 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual FVector GetCombatSocketLocationByTag(FGameplayTag InSocketTypeTag) = 0;

	/// 角色扭曲到Trans方向
	/// @param InTrans 
	/// @param WarpTargetName 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void UpdateMotionWarpingTarget(FTransform InTrans, FName WarpTargetName = FName("FacingTarget")) = 0;

	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void ShowFloatingDamageText(const float Damage, bool bBlockedHit = false, bool bCriticalHit = false) = 0;

	/// 执行角色的受击动作
	/// @param Instigator 
	virtual void ExecuteHitReact(AActor* Instigator) = 0;
};
