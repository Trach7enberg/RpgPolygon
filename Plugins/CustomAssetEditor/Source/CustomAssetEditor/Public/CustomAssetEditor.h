// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct FCustomGraphicPinFactory;
class FSlateStyleSet;

/// 自定义资产编辑器模块
class FCustomAssetEditorModule : public IModuleInterface
{
public:
	const static FName SlateStyleSet_Name;
	const static FName SlateStyleSet_PropertyName_CustomAssetEditor_NodeAddPinIcon;
	const static FName SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeleteNodeIcon;
	const static FName SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeletePinIcon;
	/// 模块启动时运行的初始化函数
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FSlateStyleSet> StyleSet = nullptr;
	TSharedPtr<FCustomGraphicPinFactory> CustomGraphicPinFactory = nullptr;
};
