// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAssetInputConfig.h"
#include "PolyEnhancedInputComponent.generated.h"

struct FGameplayTag;
class UDataAssetInputConfig;

/**
 * 项目当前的增强输入组件
 */
UCLASS()
class RPGPOLYGON_API UPolyEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
 
public:
	/// 绑定非战斗输入,例如移动、查看
	/// @tparam UserObject 
	/// @tparam CallbackFunc 
	/// @param InInputConfig 输入配置数据资产
	/// @param InInputTag 输入标签
	/// @param TriggerEvent 触发动作
	/// @param ContextObj 上下文
	/// @param CallbackFunction 回调函数
	template <class UserObject, typename CallbackFunc>
	void BindNormalInputAction(const UDataAssetInputConfig* InInputConfig,
	                           const FGameplayTag&          InInputTag,
	                           ETriggerEvent                TriggerEvent,
	                           UserObject*                  ContextObj,
	                           CallbackFunc                 CallbackFunction);

	/// 绑定能力输入
	/// @tparam UserObject 
	/// @tparam CallbackFunc 
	/// @param InInputConfig 输入配置数据资产
	/// @param ContextObj 上下文
	/// @param InputPressedCallback 按下时的回调
	/// @param InputReleasedCallback 释放时的回调
	template <class UserObject, typename CallbackFunc>
	void BindAbilityInputActions(const UDataAssetInputConfig* InInputConfig,
	                             UserObject*                  ContextObj,
	                             CallbackFunc                 InputPressedCallback,
	                             CallbackFunc                 InputReleasedCallback);
};

template <class UserObject, typename CallbackFunc>
void UPolyEnhancedInputComponent::BindNormalInputAction(const UDataAssetInputConfig* InInputConfig,
                                                        const FGameplayTag&          InInputTag,
                                                        ETriggerEvent                TriggerEvent,
                                                        UserObject*                  ContextObj,
                                                        CallbackFunc                 CallbackFunction)
{
	checkf(InInputConfig, TEXT("DataAssetInputConfig cant be null"));
	if (auto FoundAction = InInputConfig->FindInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObj, CallbackFunction);
	}
}

template <class UserObject, typename CallbackFunc>
void UPolyEnhancedInputComponent::BindAbilityInputActions(const UDataAssetInputConfig* InInputConfig,
                                                          UserObject*                  ContextObj,
                                                          CallbackFunc                 InputPressedCallback,
                                                          CallbackFunc                 InputReleasedCallback)
{
	checkf(InInputConfig, TEXT("DataAssetInputConfig cant be null"));

	for (const auto& Config : InInputConfig->AbilityInputActionConfigs)
	{
		if (!Config.IsValid()) { continue; }
		// 绑定回调函数,最后的多个参数均为函数参数,这里为GT
		BindAction(Config.InputAction, ETriggerEvent::Started, ContextObj, InputPressedCallback, Config.InputTag);
		BindAction(Config.InputAction, ETriggerEvent::Completed, ContextObj, InputReleasedCallback, Config.InputTag);
	}
}
