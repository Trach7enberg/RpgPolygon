// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FCustomAssetEditorApp;

/**
 * 自定义编辑器的模式
 * 编辑器中的模式（Mode）:布局方案的定义者,不同的编辑器有不同的布局模式,例如动画编辑器、行为树编辑器
 */
class CUSTOMASSETEDITOR_API FCustomAssetAppMode : public FApplicationMode
{
public:
	static const FName ModID;
	static const FName TabLayoutName;

	FCustomAssetAppMode(const TSharedRef<FCustomAssetEditorApp>& InApp);
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	/// 编辑器窗口主控类
	TWeakPtr<FCustomAssetEditorApp> CurrentApp{};

	/// 存储已经注册的标签页工厂
	FWorkflowAllowedTabSet CurrentTabSet{};

	
};
