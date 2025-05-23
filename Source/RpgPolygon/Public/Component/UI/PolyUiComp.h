// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PawnUiComp.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "PolyUiComp.generated.h"

class UPolyAbilitySysComp;
/**
 * 处理与UI通信的
 */
UCLASS()
class RPGPOLYGON_API UPolyUiComp : public UPawnUiComp
{
	GENERATED_BODY()

public:
	virtual void InitialUiComponent() override;
	/// 当血量发生变化时的回调委托
	UPROPERTY(BlueprintAssignable)
	FOnFloatValueChangeDelegate OnHealthChanged;

	/// 当蓝量发生变化时的回调委托
	UPROPERTY(BlueprintAssignable)
	FOnFloatValueChangeDelegate OnManaChanged;

	/// 当owner角色在移动还是不在移动时的回调委托
	FOnMovingChangeDelegate OnMovingChangeDelegateDelegate;

	/// 广播委托的初始值
	UFUNCTION(BlueprintCallable, Category="PolyGiSubSystem")
	void BroadcastHealthManaInitValue();

	virtual void BeginDestroy() override;
};
