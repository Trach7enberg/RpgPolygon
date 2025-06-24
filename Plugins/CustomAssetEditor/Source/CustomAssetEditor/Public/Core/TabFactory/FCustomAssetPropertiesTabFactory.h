// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FCustomAssetEditorApp;

/**
 * 资产属性标签页工厂
 */
class CUSTOMASSETEDITOR_API FCustomAssetPropertiesTabFactory : public FWorkflowTabFactory
{
public:
	static const FName TabFactoryID;
	FCustomAssetPropertiesTabFactory(const TSharedPtr<FCustomAssetEditorApp>& InApp);

	/// Tab 下的实际内容
	/// @param Info 
	/// @return 
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText               GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FTabSpawnerEntry&   RegisterTabSpawner(TSharedRef<FTabManager> TabManager,
	                                             const FApplicationMode*   CurrentApplicationMode) const override;
	virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<FCustomAssetEditorApp> CurrentApp;
};
