// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssetStartUp.generated.h"

enum class ERoleType : uint8;
class UGameplayEffect;
class UGameplayAbilityBase;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UDataAssetStartUp : public UDataAsset
{
	GENERATED_BODY()

public:
	/// 角色职业
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp")
	ERoleType RoleType;

	/// 默认各种角色的通用初始能力数组
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp|Abilites")
	TArray<TSubclassOf<UGameplayAbilityBase>> StartUpAbilities{};

	/// 默认某个特定条件下触发的能力数组
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp|Abilites")
	TArray<TSubclassOf<UGameplayAbilityBase>> ReactAbilities{};

	/// 角色的初始主要GE,给予顺序 1
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp|GameplayEffect")
	TSubclassOf<UGameplayEffect> PrimaryAttributes{};

	/// 角色的初始次要GE,给予顺序 2
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp|GameplayEffect")
	TSubclassOf<UGameplayEffect> SecondaryAttributes{};

	/// 角色的次要抵抗属性,给予顺序 3
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StartUp|GameplayEffect")
	TSubclassOf<UGameplayEffect> SecondaryResistanceAttributes{};

};
