// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 定义自定义资产在内容浏览器中的外观、行为和交互方式
 */
class CUSTOMASSETEDITOR_API FCustomAssetAction : public FAssetTypeActions_Base
{
public:
	FCustomAssetAction(EAssetTypeCategories::Type InAssetCategory);
	/// 内容浏览器 中显示的 名称 如 "Static Mesh"、"Blueprint"
	/// @return 
	virtual FText GetName() const override;

	/// 返回该资产类型在 内容浏览器 中的 显示颜色 如 FColor::Blue
	/// 注意 会应用叠加到Tab Icon 图标的颜色上会导致失真
	/// @return 
	virtual FColor GetTypeColor() const override;
	
	/// 返回该 FAssetTypeActions 支持的 UClass资产类,如 UStaticMesh::StaticClass()
	/// @return 
	virtual UClass* GetSupportedClass() const override;

	/// 定义 双击资产 或 右键菜单选择 "Edit" 时的行为
	/// @param InObjects 
	/// @param EditWithinLevelEditor 
	virtual void OpenAssetEditor(const TArray<UObject*>&        InObjects,
	                             TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<
		                             IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type _AssetCategory;
};
