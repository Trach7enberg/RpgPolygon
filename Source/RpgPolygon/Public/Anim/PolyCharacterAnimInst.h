// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/CharacterAnimInstBase.h"
#include "PolyCharacterAnimInst.generated.h"


class APolyCharacter;
/**
 * 玩家角色动画蓝图基类
 */
UCLASS()
class RPGPOLYGON_API UPolyCharacterAnimInst : public UCharacterAnimInstBase
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	/// 获取当前动画蓝图Owner的角色(玩家)
	UFUNCTION(BlueprintCallable, Category="PolyAnim")
	APolyCharacter* GetOwningPolyCharacter();

protected:
	/// 当前蓝图owner,即玩家的实例
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TWeakObjectPtr<APolyCharacter> OwningPolyCharacter = nullptr;
};
