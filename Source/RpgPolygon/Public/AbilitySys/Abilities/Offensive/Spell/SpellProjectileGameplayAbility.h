// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "RpgPolygon/Public/AbilitySys/Abilities/Offensive/PlayerOffensiveGameplayAbility.h"
#include "SpellProjectileGameplayAbility.generated.h"

struct FPolyProjectileDamageEffectParam;
class APolyProjectileBase;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API USpellProjectileGameplayAbility : public UPlayerOffensiveGameplayAbility
{
	GENERATED_BODY()

public:
	USpellProjectileGameplayAbility();

	/// 生成投射物
	/// @param HitResult 击中数据
	/// @param InAttackSocketLoc 生成飞弹的初始位置Socket,该Socket与对应的游戏标签相关联
	UFUNCTION(BlueprintCallable, Category="PolyAbility|SpellProjectile")
	virtual void SpawnProjectile(const FHitResult& HitResult, FVector InAttackSocketLoc);

	/// 生成多重投射物,(投射物有追踪效果) 
	/// @param HitResult 
	/// @param InAttackSocketLoc
	/// @param HomingActor	飞弹的追踪目标
	/// @param bOverridePitch 是否覆盖俯仰角
	/// @param OverridePitch 俯仰角度
	UFUNCTION(BlueprintCallable, Category="PolyAbility|SpellProjectile")
	virtual void SpawnProjectiles(const FHitResult& HitResult,
	                              FVector           InAttackSocketLoc,
	                              AActor*           HomingActor,
	                              bool              bOverridePitch,
	                              float             OverridePitch);

	virtual void MakeProjectileDamageEffectParamsFromAbilityDefaults(FPolyProjectileDamageEffectParam& OutParam,
	                                                                 AActor*                           Target) const;

protected:
	/// 生成多重射弹时的散射度
	UPROPERTY(EditDefaultsOnly, Category="PolyAbility|SpellProjectile", meta=(ClampMin="0", ClampMax="360"))
	float SpawnSpread = 90.f;

	/// 当前能力能够生成的最大射弹数
	UPROPERTY(EditDefaultsOnly, Category="PolyAbility|SpellProjectile")
	int32 MaxProjectileNum = 5;

	/// 射弹是否追踪
	UPROPERTY(EditDefaultsOnly, Category="PolyAbility|SpellProjectile")
	bool bIsHomingProjectile = false;

	/// 射弹是否启用重力
	UPROPERTY(EditDefaultsOnly, Category="PolyAbility|SpellProjectile", meta=(ClampMin="0", ClampMax="10"))
	float ProjectileGravity = 0.f;

	/// 追踪射弹的最小加速度
	UPROPERTY(EditDefaultsOnly, Category="PolyAbility|SpellProjectile")
	float HomingMinAcceleration = 1600.f;

	/// 追踪射弹的最大加速度
	UPROPERTY(EditDefaultsOnly, Category="PolyAbility|SpellProjectile")
	float HomingMaxAcceleration = 3200.f;

	/// 飞弹实体类
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		meta=(AssetRegistrySearchable = true),
		Category="PolyAbility|SpellProjectile")
	TSoftClassPtr<APolyProjectileBase> ProjectileClass;

	/// 鼠标点击的位置,如果飞弹的追踪目标无法获取则设置为这个组件
	UPROPERTY()
	TObjectPtr<USceneComponent> NonHomingTarget;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle     Handle,
	                             const FGameplayAbilityActorInfo*     ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData*            TriggerEventData) override;


	/// 创建生成飞弹实例
	/// @param Transform 
	/// @param Instigator 
	/// @return 
	APolyProjectileBase* CreateProjectile(const FTransform& Transform, APawn* Instigator) const;
};
