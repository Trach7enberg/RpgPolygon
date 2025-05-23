// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/PawnCombatComp.h"
#include "Interface/CombatInterface.h"
#include "EnemyCombatComp.generated.h"

class UEnemyWeaponComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UEnemyCombatComp : public UPawnCombatComp, public ICombatInterface
{
	GENERATED_BODY()

public:
	UEnemyCombatComp();
	virtual void InitDependencies(UPawnWeaponComp* InPawnWeaponComp, UMotionWarpingComponent* InMotionWarpingComp) override;
	//~Begin ICombatInterface

	/// 只在服务器端进行检测,开启战斗武器检测Overlap
	/// @param bShouldEnable 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void EnableWeaponCombatDetect(bool bShouldEnable) override;

	/// 获取玩家准备死亡时的委托(播放死亡动画时)
	/// @return 
	virtual FOnPreDeathSignature& GetCharacterPreOnDeathDelegate() override;

	/// 获取当前战斗插槽位置
	/// @param InSocketTypeTag 
	/// @return 
	virtual FVector GetCombatSocketLocationByTag(FGameplayTag InSocketTypeTag) override;

	/// 角色扭曲到Trans方向
	/// @param InTrans 
	/// @param WarpTargetName 
	virtual void UpdateMotionWarpingTarget(FTransform InTrans, FName WarpTargetName = FName("FacingTarget")) override;
	virtual void
	ShowFloatingDamageText(const float Damage, bool bBlockedHit = false, bool bCriticalHit = false) override;
	virtual void ExecuteHitReact(AActor* Instigator) override;
	//~End ICombatInterface

protected:
	UEnemyWeaponComp* GetOwningEnemyWeaponComp() ;

private:
	TWeakObjectPtr<UEnemyWeaponComp> OwningEnemyWeaponComp;
};
