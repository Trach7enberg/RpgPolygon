// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySys/Core/PawnAttributeSet.h"
#include "PolyAttributeSet.generated.h"

class UPolyAbilitySysComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPolyAttributeSet : public UPawnAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	/// 这个函数在游戏效果改变一个属性之后被执行
	/// @param Data 
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

#pragma region PrimaryAttri
	/// Primary 属性 6 个
	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, Category = "Primary Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, Strength);

	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, BlueprintReadOnly, Category = "Primary Attribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, Intelligence);

	UPROPERTY(ReplicatedUsing = OnRep_Resilience, BlueprintReadOnly, Category = "Primary Attribute")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, Resilience);

	UPROPERTY(ReplicatedUsing = OnRep_Vigor, BlueprintReadOnly, Category = "Primary Attribute")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, Vigor);

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Vital Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, MaxHealth);

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Vital Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, MaxMana);

#pragma endregion

#pragma region  SecondaryAttr
	/// Second Primary属性 9 个
	UPROPERTY(ReplicatedUsing = OnRep_Armor, BlueprintReadOnly, Category = "Second Primary Attribute")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, Armor);

	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, BlueprintReadOnly, Category = "Second Primary Attribute")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, ArmorPenetration);

	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, BlueprintReadOnly, Category = "Second Primary Attribute")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, BlockChance);

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChance, BlueprintReadOnly, Category = "Second Primary Attribute")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, CriticalHitChance);

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage, BlueprintReadOnly, Category = "Second Primary Attribute")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, CriticalHitDamage);

	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, BlueprintReadOnly, Category = "Second Primary Attribute")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, HealthRegeneration);

	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, BlueprintReadOnly, Category = "Second Primary Attribute")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, ManaRegeneration);

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, CurrentHealth);

	UPROPERTY(ReplicatedUsing = OnRep_CurrentMana, BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, CurrentMana);

#pragma endregion

#pragma region Secondary Resistance
	/// Secondary Resistance属性 5 个
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance,
		BlueprintReadOnly,
		Category = "Second Primary Attribute|Resistance")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, CriticalHitResistance);

	UPROPERTY(ReplicatedUsing = OnRep_FireResistance,
		BlueprintReadOnly,
		Category = "Second Primary Attribute|Resistance")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, FireResistance);

	UPROPERTY(ReplicatedUsing = OnRep_PhysicalResistance,
		BlueprintReadOnly,
		Category = "Second Primary Attribute|Resistance")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, PhysicalResistance);

	UPROPERTY(ReplicatedUsing = OnRep_LightingResistance,
		BlueprintReadOnly,
		Category = "Second Primary Attribute|Resistance")
	FGameplayAttributeData LightingResistance;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, LightingResistance);

	UPROPERTY(ReplicatedUsing = OnRep_ArcaneResistance,
		BlueprintReadOnly,
		Category = "Second Primary Attribute|Resistance")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, ArcaneResistance);

#pragma endregion

#pragma region MetaAttri
	/// Meta属性
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData InComingDamage;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, InComingDamage);

	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UPolyAttributeSet, IncomingXP);

#pragma endregion

#pragma region  OnRepFunc
	/// Primary OnRep
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldValue) const;


	/// Secondary OnRep
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;

	/// Secondary Resistance OnRep
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_LightingResistance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldValue) const;

	/**
	 *  Vital OnRep
	 *  CurrentHealth变量复制到客户端的时候,就会调用该函数
	 *  该函数可以接受1个参数,但是必须也是FGameplayAttributeData类型的
	 *  当有一个参数时,它将是旧值作为参数
	 */
	UFUNCTION()
	void OnRep_CurrentHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_CurrentMana(const FGameplayAttributeData& OldValue) const;
#pragma endregion
	
	/// 获取我们定义的能力系统组件
	/// @return 能力系统组件
	UPolyAbilitySysComp* GetMyCurrentAbilitySystem();

private:
	TSoftObjectPtr<UPolyAbilitySysComp> CurrentPolyAbilitySystem;
};
