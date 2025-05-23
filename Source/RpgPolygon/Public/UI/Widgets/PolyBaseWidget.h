// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "PolyBaseWidget.generated.h"

class UPolyGiSubSystem;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPolyBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="PolyWidget")
	FGameplayTag GetPolyWidgetTag() const { return PolyWidgetTag; }

	UFUNCTION(BlueprintCallable, Category="PolyWidget")
	void SetPolyWidgetTag(const FGameplayTag& NewGameplayTag) { this->PolyWidgetTag = NewGameplayTag; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyWidget")
	UPolyGiSubSystem* GetPolyGiSubSystem();

	/// 根据给定的父类Transform Render Angle 计算旋转回水平值所需要的差值
	/// @param ParentRootRenderAngle 
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyWidget")
	float CalculateHorizontalOffset(float ParentRootRenderAngle);

	/// 初始化polyWidget
	UFUNCTION(BlueprintCallable, Category="PolyWidget")
	virtual void InitializePolyWidget();

protected:
	/// 当被初始化时调用该事件
	UFUNCTION(BlueprintImplementableEvent, Category="PolyWidget")
	void OnPolyWidgetInitialize();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyWidget")
	FGameplayTag PolyWidgetTag{};

private:
	TWeakObjectPtr<UPolyGiSubSystem> PolyGiSubSystem{};
};
