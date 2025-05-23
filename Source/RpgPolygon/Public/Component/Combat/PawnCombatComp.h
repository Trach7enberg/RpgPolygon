// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "PawnCombatComp.generated.h"

class UMotionWarpingComponent;
class UPawnWeaponComp;
struct FGenericTeamId;
class UFloatingTextWidgetComponent;
class UObjectPoolSubsystem;
/**
 * 基础战斗组件,包括攻击、伤害等
 */
UCLASS()
class RPGPOLYGON_API UPawnCombatComp : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	/// 初始化组件依赖
	/// @param InPawnWeaponComp 
	/// @param InMotionWarpingComp 
	virtual void InitDependencies(UPawnWeaponComp* InPawnWeaponComp, UMotionWarpingComponent* InMotionWarpingComp);

	/// 
	/// @param AttackActor 
	/// @return 
	bool IsValidBlock(const AActor* AttackActor) const;

	/// 广播当前玩家(组件的Owner)准备死亡
	void BroadcastOnPreDeath() const;

	/// 获取玩家准备死亡时的委托(播放死亡动画时)
	/// @return 
	FOnPreDeathSignature& GetOnPreDeathSignature() { return OnPreDeathDelegate; }


	void ShowFloatingDamageStr(const float Damage, bool bBlockedHit = false, bool bCriticalHit = false);

	/// 发送战斗能力事件
	/// @param Receive 
	/// @param InEventTag 
	/// @param Payload 
	UFUNCTION(BlueprintCallable, Category="CombatComp")
	virtual void SendCombatGameplayEvent(AActor*             Receive,
	                                     const FGameplayTag& InEventTag,
	                                     FGameplayEventData  Payload);


protected:
	FOnPreDeathSignature  OnPreDeathDelegate;
	UObjectPoolSubsystem* GetObjectPoolSubsystem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PawnCombatComp")
	TSubclassOf<UFloatingTextWidgetComponent> DamageTextWidgetClass{};

	FORCEINLINE UPawnWeaponComp*         GetOwningPawnWeaponComp() const;
	FORCEINLINE UMotionWarpingComponent* GetOwningMotionWarpingComponent() const;

private:
	TWeakObjectPtr<UObjectPoolSubsystem>    ObjectPoolSubsystem{};
	TWeakObjectPtr<UPawnWeaponComp>         OwningPawnWeaponComp;
	TWeakObjectPtr<UMotionWarpingComponent> OwningMotionWarpingComponent;
};
