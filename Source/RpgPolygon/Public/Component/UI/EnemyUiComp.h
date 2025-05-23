// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PawnUiComp.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "EnemyUiComp.generated.h"

struct FOnAttributeChangeData;

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UEnemyUiComp : public UPawnUiComp
{
	GENERATED_BODY()

public:
	virtual void InitializePawnComponent() override;

	/// 用于敌方Widget中绑定血量响应的委托
	UPROPERTY(BlueprintAssignable)
	FOnFloatValueChangeDelegate OnEnemyHealthChanged;

	/// 用于敌方Widget中绑定蓝量响应的委托
	UPROPERTY(BlueprintAssignable)
	FOnFloatValueChangeDelegate OnEnemyManaChanged;

	/// 广播委托的初始值
	UFUNCTION(BlueprintCallable, Category="PolyGiSubSystem")
	void BroadcastHealthManaInitValue();

protected:
	UFUNCTION(Client, Unreliable)
	void Client_BroadcastOnEnemyHealthChanged(float New,float Old = 0.f);
};
