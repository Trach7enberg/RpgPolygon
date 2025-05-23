// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PolyAnimInstBase.generated.h"

class UCharacterMovementComponent;
struct FGameplayTag;
class APolyCharacterBase;
/**
 * 动画实例基础类
 */
UCLASS()
class RPGPOLYGON_API UPolyAnimInstBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	/// 用于 线程安全地更新动画 的函数，通常用来在多线程环境下进行动画更新时,确保动画状态的安全性
	/// 在多核处理器中,该函数可以使得某些动画计算任务在后台线程进行,而主线程不需要等待它们完成,从而提高游戏的帧率和响应速度
	/// @param DeltaSeconds 
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(Blueprintable, BlueprintPure, Category="PolyAnim")
	bool DoesOwnerHasTag(FGameplayTag TagToCheck) const;

protected:
	/// 当前动画蓝图owner的角色的基类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Comp")
	TObjectPtr<APolyCharacterBase> OwningCharacter{};

	/// 当前动画蓝图owner的角色的基类的移动组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Comp")
	TObjectPtr<UCharacterMovementComponent> OwningMovementComp{};

	/// 角色的地面速度
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	float GroundSpeed{};

	/// 是否有加速度,在移动?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	bool bHasAcceleration{};

	/// 在掉落?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	bool bIsFalling{};

	/// 是否进入空闲状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	bool bShouldEnterRelaxState = false;

	/// 空闲阈值,空闲N秒则进入relax
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	float EnterRelaxStateThreshold = 5.f;

	/// 空闲阈值的tolerance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	float RandomRelaxStateThreshold = 1.f;

	/// 当前已经空闲了的时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	float IdleElapsedTime{};

	/// 角色当前的移动方向
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAnim|Locomotion")
	float LocomotionDirection{};
};
