// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/Interactive/PawnIntercatComp.h"
#include "PolyInteractComp.generated.h"

struct FGameplayTag;
/**
 * 玩家的互动组件
 */
UCLASS()
class RPGPOLYGON_API UPolyInteractComp : public UPawnInteractComp
{
	GENERATED_BODY()

public:
	/// 解析鼠标(左键)点击的输入标签分发对应动作
	/// 因为多个能力都是由鼠标左键触发这里需要分析判断为启用哪个左键的输入标签,因此和左键无关的直接返回
	/// @param InInputTag 
	/// @return 
	FGameplayTag AnalyzeAbilityClickInputTag(const FGameplayTag& InInputTag);

	/// 
	/// @param InGt 
	void SendAbilityStatusTag(const FGameplayTag& InGt) const;
	
	/// 
	/// @param InGt 
	void RemoveAbilityStatusTag(const FGameplayTag& InGt) const;

protected:
	APlayerController* GetOwningPlayerController();

private:
	TWeakObjectPtr<APlayerController> OwningPlayerController;
};
