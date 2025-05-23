// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/PawnExtensionComponentBase.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "PawnWeaponComp.generated.h"

class UPawnCombatComp;
struct FGameplayEventData;
enum class EEquippedState : uint8;
class APolyWeaponBase;
struct FWeaponInstance;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPawnWeaponComp : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UPawnWeaponComp();


	/// 注册武器并存储起来
	/// @param InGt 武器标签
	/// @param InWeapon 武器实体
	/// @param RegisterAndEquippedNow 注册时并立马装备
	UFUNCTION(BlueprintCallable, Category="WeaponComp")
	void RegisterSpawnedWeapon(UPARAM(ref) const FGameplayTag& InGt,
	                           APolyWeaponBase*                InWeapon,
	                           bool                            RegisterAndEquippedNow);

	/// 通过GT获取武器
	/// @param InGt 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="WeaponComp")
	APolyWeaponBase* GetWeaponByTag(UPARAM(ref) const FGameplayTag& InGt);

	/// 获取当前武器的基础伤害
	/// @param InLevel 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="WeaponComp")
	virtual float GetCurrentEquippedWeaponDamage(float InLevel);

	UFUNCTION(Server,Reliable, Category="WeaponComp")
	void SetCurrentWeaponTag(const FGameplayTag& InGt);

	/// 获取当前已准备的武器
	/// @return 
	UFUNCTION(BlueprintCallable, Category="WeaponComp")
	APolyWeaponBase* GetCurrentWeapon();


	/// 
	/// @tparam T 
	/// @param InGt 
	/// @return 
	template <class T = APolyWeaponBase>
	UFUNCTION(BlueprintCallable, Category="WeaponComp")
	T* GetWeaponByTag(UPARAM(ref) const FGameplayTag& InGt)
	{
		static_assert(TPointerIsConvertibleFromTo<T, APolyWeaponBase>::Value,
		              "T must be inherited from PolyWeaponBase");
		const auto TmpWeapon = GetWeaponByTag(InGt);
		return TmpWeapon ? CastChecked<T>(TmpWeapon) : nullptr;
	}

	/// 启用武器碰撞检测,主要用于刀、剑类武器
	/// @param bShouldEnable 
	/// @param EquippedState 
	virtual void EnableWeaponCollision(bool           bShouldEnable,
	                                   EEquippedState EquippedState = EEquippedState::Current);

	

	FORCEINLINE float GetWeaponDataBaseDamage(float InAbilityLevel = 1);

	void DestroyWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FVector GetWeaponSocketLocationByTag(const FGameplayTag& InSocketType);

	virtual void InitializePawnComponent() override;

protected:
	// 当前(正装备的)武器的标签
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Replicated,
		ReplicatedUsing=OnRep_CurrentEquippedWeaponTag,
		Category="WeaponComp")
	FGameplayTag CurrentEquippedWeaponTag{};

	UPROPERTY()
	TArray<AActor*> OverlappedActors{};

	
	UPawnCombatComp* GetOwningCombatComp();
private:
	UPROPERTY(Replicated, ReplicatedUsing=OnRep_WeaponArrays)
	TArray<FWeaponInstance> WeaponArrays{};

	UPROPERTY()
	TWeakObjectPtr<UPawnCombatComp> OwningCombatComp;


	virtual void OnWeaponBeginHit(AActor* HitActor, const FHitResult* HitResult);
	virtual void OnWeaponEndHit(AActor* HitActor, const FHitResult* HitResult);


	UFUNCTION()
	void OnRep_WeaponArrays();

	UFUNCTION()
	void OnRep_CurrentEquippedWeaponTag(FGameplayTag OldValue);
};

inline void UPawnWeaponComp::SetCurrentWeaponTag_Implementation(const FGameplayTag& InGt)
{
	this->CurrentEquippedWeaponTag = InGt;
}
