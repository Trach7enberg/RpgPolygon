// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "EditorUndoClient.h"
#include "Misc/NotifyHook.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UEdGraph;
class UCustomAsset;
/**
 * 编辑器窗口”的主控类，负责加载界面、标签页、布局、工具栏等所有行为的入口
 * 任何窗口、编辑器都继承自FWorkflowCentricApplication
 */
class CUSTOMASSETEDITOR_API FCustomAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient,
                                                    public FNotifyHook
{
public:
	const static FName AppID;
	const static FName GraphName;

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	void         InitEditor(const EToolkitMode::Type        InMode,
	                        const TSharedPtr<IToolkitHost>& InitToolkitHost,
	                        UObject*                        InObj);

public:
	FORCEINLINE virtual FName GetToolkitFName() const override { return FName(TEXT("CustomAssetEditorApp")); }
	FORCEINLINE virtual FText GetBaseToolkitName() const override
	{
		return NSLOCTEXT("CustomAssetEditorApp", "AppLabel", "CustomAssetEditorApp");
	};
	FORCEINLINE virtual FString GetDocumentationLink() const override
	{
		return TEXT("https://github.com/Trach7enberg/RpgPolygon");
	};

	/// 当别的编辑器窗口（Toolkit）被拖动进当前这个资产编辑器窗口时
	/// @param Toolkit 
	FORCEINLINE virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override {};

	/// 当别的编辑器窗口（Toolkit）被拖出当前这个资产编辑器窗口时
	/// @param Toolkit 
	FORCEINLINE virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override {};
	FORCEINLINE virtual FString GetWorldCentricTabPrefix() const override { return FString("CustomAssetEditorApp"); };
	FORCEINLINE virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; };

	FORCEINLINE UCustomAsset* GetCurrentCustomAsset() const { return CurrentCustomAsset; }

	FORCEINLINE void SetCurrentCustomAsset(UCustomAsset& InCurrentCustomAsset)
	{
		this->CurrentCustomAsset = InCurrentCustomAsset;
	}

	FORCEINLINE UEdGraph* GetCurrentGraph() const { return CurrentGraph; }

protected:
	/// 将Graph保存至自定义资产
	void UpdateAssetFromGraph();

	/// 读取自定义资产数据到Graph
	void UpdateEditorGraphFromAsset();

private:
	/// 编辑器中的资产(保存的数据之类的)
	TObjectPtr<UCustomAsset> CurrentCustomAsset = nullptr;

	/// 当前的自定义编辑器资产图表graph
	TObjectPtr<UEdGraph> CurrentGraph = nullptr;
};
