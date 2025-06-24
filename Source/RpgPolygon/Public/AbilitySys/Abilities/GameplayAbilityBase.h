// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

class UNiagaraSystem;
class APolyCharacterBase;
class UPawnWeaponComp;
enum class EPolyAbilityActivationPolicy : uint8;
enum class EPolyConfirmType : uint8;
class UPawnCombatComp;
class UPolyAbilitySysComp;
/**
 * 基础能力
 */
UCLASS()
class RPGPOLYGON_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbilityBase();

	/// 获取化身角色
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	APolyCharacterBase* GetAvatarCharacter();

	/// 获取化身的控制器
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	AController* GetPawnController();

	/// 获取化身角色的战斗组件
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	UPawnCombatComp* GetPawnCombatComp();

	/// 获取化身角色的武器组件
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	UPawnWeaponComp* GetPawnWeaponComp();

	/// 获取能力系统
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	UPolyAbilitySysComp* GetPolyAbilitySysComp();

	/// 制作 Damage GE
	/// @param GeClass 
	/// @param InCurrentAttackTypeTag 
	/// @param InComboCount 
	/// @param InWeaponBaseDamage 
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility|Damage")
	virtual FGameplayEffectSpecHandle MakeDamageEffectSpecHandle(const TSubclassOf<UGameplayEffect>& GeClass,
	                                                             const FGameplayTag InCurrentAttackTypeTag,
	                                                             float InComboCount = 1.f,
	                                                             float InWeaponBaseDamage = 1.f);


	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs="OutConfirm"), Category="PolyAbility|Damage")
	FActiveGameplayEffectHandle ApplyDamageEffectSpecToTarget(AActor*                          Target,
	                                                          const FGameplayEffectSpecHandle& InSpecHandle,
	                                                          EPolyConfirmType&                OutConfirm);

	/// 设置拥有者的Mesh单个材质参数值
	/// @param InParameterName 
	/// @param InParameterValue 
	UFUNCTION(BlueprintCallable, Category="PolyAbility")
	virtual void SetScalarParameterOnOwnerMeshMaterials(FName InParameterName, float InParameterValue);

	/// 获取随机蒙太奇动画
	/// @param InMontages 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="PolyAbility")
	virtual UAnimMontage* GetRandomMontage(const TArray<UAnimMontage*>& InMontages) const;
	

	/// 在客户端生成VFX
	/// @param InNiagaraSystem 
	/// @param InLoc 
	UFUNCTION(BlueprintCallable, Category="PolyAbility|Vfx")
	virtual void Client_SpawnSystemAtLoc(TSoftObjectPtr<UNiagaraSystem> InNiagaraSystem, const FVector InLoc);

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle     Handle,
	                        const FGameplayAbilityActorInfo*     ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo,
	                        bool                                 bReplicateEndAbility,
	                        bool                                 bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category="PolyAbility")
	EPolyAbilityActivationPolicy AbilityActivationPolicy{};


	/// 伤害GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAbility")
	TSubclassOf<UGameplayEffect> DamageEffectClass{};

	/// 获取当前随机的攻击动画
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility")
	virtual UAnimMontage* GetCurrentAttackMontage() const;

private:
	UPROPERTY()
	TWeakObjectPtr<AController> OwningPawnController{};

	UPROPERTY()
	TWeakObjectPtr<APolyCharacterBase> OwningCharacter{};

	UPROPERTY()
	TWeakObjectPtr<UPawnCombatComp> OwningPawnCombatComp{};

	UPROPERTY()
	TWeakObjectPtr<UPawnWeaponComp> OwningPawnWeaponComp{};

	UPROPERTY()
	TWeakObjectPtr<UPolyAbilitySysComp> OwningPolyAbilitySysComp{};
};
