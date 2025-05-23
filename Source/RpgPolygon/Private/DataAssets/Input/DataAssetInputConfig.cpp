// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAssetInputConfig.h"

UInputAction* UDataAssetInputConfig::FindInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const auto& [InputTag, InputAction] : InputActionConfigs)
	{
		if (InputTag == InInputTag && InputAction) { return InputAction; }
	}
	return nullptr;
}
