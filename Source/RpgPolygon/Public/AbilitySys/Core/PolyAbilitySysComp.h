// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySys/Core/PawnAbilitySysComp.h"
#include "PolyAbilitySysComp.generated.h"

class UGameplayAbilityBase;
struct FPolyAbilityStruct;
class UEnemyGameplayAbility;
class UPolyGiSubSystem;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPolyAbilitySysComp : public UPawnAbilitySysComp
{
	GENERATED_BODY()

public:
	virtual void InitializeComponent() override;

	/// 赋予初始能力 (默认给予时不启用能力)
	/// @param InGameAbilitiesClass 
	/// @param AbilityLevel
	/// @param GrandAndActivateOnce 为true时则在赋予能力时并启用一次,默认值为false
	virtual void GiveInitialAbilities(TArray<TSubclassOf<UGameplayAbilityBase>>& InGameAbilitiesClass,
	                                  bool                                       GrandAndActivateOnce = false,
	                                  float                                      AbilityLevel         = 1.f);

	/// 赋予初始(敌人的)能力 (默认给予时不启用能力)
	/// @param InEnemyGameAbilitiesClass 
	/// @param AbilityLevel 
	/// @param GrandAndActivateOnce 
	virtual void GiveInitialAbilities(TArray<TSubclassOf<UEnemyGameplayAbility>>& InEnemyGameAbilitiesClass,
	                                  float                                       AbilityLevel         = 1.f,
	                                  bool                                        GrandAndActivateOnce = false);

	/// 赋予初始(英雄的)能力 (默认给予时不启用能力)
	/// @param InPolyAbilityStruct 
	/// @param GrandAndActivateOnce 
	/// @param AbilityLevel 
	virtual void GiveInitialAbilities(TArray<FPolyAbilityStruct>& InPolyAbilityStruct,
	                                  bool                        GrandAndActivateOnce = false,
	                                  float                       AbilityLevel         = 1.f);

	/// 给予初始能力
	/// @param InPolyAbilityStruct 
	/// @param OutSpecHandles 
	/// @param AbilityLevel
	virtual void GiveInitialAbilities(const TArray<FPolyAbilityStruct>&   InPolyAbilityStruct,
	                                  TArray<FGameplayAbilitySpecHandle>& OutSpecHandles,
	                                  float                               AbilityLevel = 1.f);

	virtual void ApplyInitialGameplayEffectToSelf(TArray<TSubclassOf<UGameplayEffect>> GameplayEffects,
	                                        float                                AbilityLevel = 1.f);

	/// 尝试通过标签启用能力
	/// @param AbilityTag 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="WarriorAsc")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTag);

	virtual void GrantAbility(TSubclassOf<UGameplayAbility> InAbility,
	                          float                         AbilityLevel,
	                          bool                          GrandAndActivateOnce = true);

	/// 通过输入标签获取能力
	/// @param InInputTag 
	/// @return 
	FGameplayAbilitySpec* GetAbilitySpecByInputTag(const FGameplayTag& InInputTag);

	/// 取消并且清除SpecHandle数组里对应spec的能力
	/// @param InSpecHandles 
	/// @return 
	void ClearAbilities(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputRelease(const FGameplayTag& InInputTag);

private:
	UPROPERTY()
	TObjectPtr<UPolyGiSubSystem> GiSubSystem = nullptr;
};
