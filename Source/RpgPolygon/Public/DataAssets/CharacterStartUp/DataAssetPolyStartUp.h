// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/CharacterStartUp/DataAssetStartUp.h"
#include "DataAssetPolyStartUp.generated.h"

struct FPolyAbilityStruct;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UDataAssetPolyStartUp : public UDataAssetStartUp
{
	GENERATED_BODY()

public:
	/// 英雄角色的初始技能,默认给予时不会触发
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(TitleProperty="InputTag"), Category="PolyStartUp")
	TArray<FPolyAbilityStruct> PlayerStartupAbilities{};
};
