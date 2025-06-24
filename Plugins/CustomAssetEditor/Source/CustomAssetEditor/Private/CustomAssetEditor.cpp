// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditor.h"

#include "IAssetTools.h"
#include "Core/CustomAssetAction.h"
#include "Graph/CustomGraphicPinFactory.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

const FName FCustomAssetEditorModule::SlateStyleSet_Name("CustomAssetEditor");
const FName
FCustomAssetEditorModule::SlateStyleSet_PropertyName_CustomAssetEditor_NodeAddPinIcon("CustomAssetEditor.NodeAddPinIcon");
const FName
FCustomAssetEditorModule::SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeleteNodeIcon("CustomAssetEditor.NodeDeleteNodeIcon");
const FName
FCustomAssetEditorModule::SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeletePinIcon("CustomAssetEditor.NodeDeletePinIcon");

void FCustomAssetEditorModule::StartupModule()
{
	// IAssetTools 是一个引擎内置的接口,用来注册/管理各种资产类型Asset Type Actions和分类等
	IAssetTools& InAssetTools = IAssetTools::Get();

	//把自定义的资产类型(通过 FCustomAssetAction 定义的行为)注册到 UE 的内容浏览器系统中,并分到一个叫 "Asset Category" 的分类里
	EAssetTypeCategories::Type AssetType = InAssetTools.RegisterAdvancedAssetCategory("CustomAssets",
			 NSLOCTEXT("MyAssetCategory", "MyAssetCategory", "CustomAssets"));

	// 把写好的 FCustomAssetAction 注册到 UE 的资产系统中
	TSharedPtr<FCustomAssetAction> CustomAssetAction = MakeShareable(new FCustomAssetAction(AssetType));
	InAssetTools.RegisterAssetTypeActions(CustomAssetAction.ToSharedRef());

	// 资源路径
	StyleSet                = MakeShareable(new FSlateStyleSet(SlateStyleSet_Name));
	const auto ResourcePath = IPluginManager::Get().FindPlugin(SlateStyleSet_Name.ToString())->GetContentDir() /
			TEXT("Resources");
	StyleSet->SetContentRoot(ResourcePath);

	CustomGraphicPinFactory = MakeShareable(new FCustomGraphicPinFactory());

	// 设置asset的contentBrowser缩略图和TabIcon图标
	const auto ThumbNailBrush
			= new FSlateImageBrush(StyleSet->
			                       RootToContentDir(TEXT("CustomAssetThumbnail"),TEXT(".png")),
			                       FVector2D(128.0, 128.0));
	const auto IconBrush_CustomAssetIcon
			= new FSlateImageBrush(
			                       StyleSet->
			                       RootToContentDir(TEXT("CustomAssetIcon"),TEXT(".png")),
			                       FVector2D(128.0, 128.0));
	const auto IconBrush_NodeAddPinIcon
			= new FSlateImageBrush(
			                       StyleSet->
			                       RootToContentDir(TEXT("NodeAddPinIcon"),TEXT(".png")),
			                       FVector2D(128.0, 128.0));
	const auto IconBrush_NodeDeleteNodeIcon
			= new FSlateImageBrush(StyleSet->
			                       RootToContentDir(TEXT("NodeDeleteNodeIcon"),TEXT(".png")),
			                       FVector2D(128.0, 128.0));
	const auto IconBrush_NodeDeletePinIcon
			= new FSlateImageBrush(StyleSet->
			                       RootToContentDir(TEXT("NodeDeletePinIcon"), TEXT(".png")),
			                       FVector2D(128.0, 128.0));

	// 这里存储覆盖的引擎系统资源,当编辑器需要显示某个资产的图标时，它会根据资产的类名构造样式键名，并在已注册的样式集中查找对应的样式
	StyleSet->Set(TEXT("ClassThumbnail.CustomAsset"), ThumbNailBrush);
	StyleSet->Set(TEXT("ClassIcon.CustomAsset"), IconBrush_CustomAssetIcon);
	// 自定义写法,要用的时候直接get就行
	StyleSet->Set(SlateStyleSet_PropertyName_CustomAssetEditor_NodeAddPinIcon, IconBrush_NodeAddPinIcon);
	StyleSet->Set(SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeleteNodeIcon, IconBrush_NodeDeleteNodeIcon);
	StyleSet->Set(SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeletePinIcon, IconBrush_NodeDeletePinIcon);

	FEdGraphUtilities::RegisterVisualPinFactory(CustomGraphicPinFactory);
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	TArray<FName> StyleKeys;
}

void FCustomAssetEditorModule::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(CustomGraphicPinFactory);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)
