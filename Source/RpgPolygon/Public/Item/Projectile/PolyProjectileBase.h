// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "GameFramework/Actor.h"
#include "PolyProjectileBase.generated.h"

struct FPolyProjectileDamageEffectParam;
class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class RPGPOLYGON_API APolyProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	APolyProjectileBase();

	/// 伤害数据
	FPolyProjectileDamageEffectParam DamageEffectParam{};


	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent.Get(); }

	/// 启用当飞弹的追踪目标无效时的事件
	virtual void RegisterHomingActorOnMissingEvent();

protected:
	virtual void BeginPlay() override;

	/// 飞弹是否忽略友军
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile")
	bool bIgnoreFriend = true;

	/// 飞弹最大生命周期
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile")
	float ProjectileLifeSpawn = 5.0f;

	/// 投射物击中时的效果
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile|Niagara")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	/// 特效组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile|Niagara")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	/// 冲击声
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile|Sound")
	TObjectPtr<USoundBase> ImpactSound;

	/// 循环声
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile|Sound")
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile|Collision")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PolyProjectile|Movement")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;


	/// 投射物身上的循环声音
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopSoundAudioComponent;

	/// 生成特效和声音
	virtual void SpawnVfxAndSound() const;

private:
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                  AActor*              OtherActor,
	                                  UPrimitiveComponent* OtherComp,
	                                  int32                OtherBodyIndex,
	                                  bool                 bFromSweep,
	                                  const FHitResult&    SweepResult);

	UFUNCTION()
	virtual void OnSphereEneOverlap(UPrimitiveComponent* OverlappedComponent,
	                                AActor*              OtherActor,
	                                UPrimitiveComponent* OtherComp,
	                                int32                OtherBodyIndex);

	/// 当飞弹的追踪目标被销毁时回调的事件
	/// @param Actor 
	UFUNCTION()
	virtual void HomingActorOnMissing(AActor* Actor);
};
