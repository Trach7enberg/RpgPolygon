// Garrett Gan All Right Reserved


#include "Core/TabFactory/FCustomAssetPropertiesTabFactory.h"

#include "CustomAssetEditorRuntime.h"
#include "PropertyEditorModule.h"
#include "Core/CustomAsset.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "Core/CustomAssetEditorApp.h"

#define LOCTEXT_NAMESPACE "CustomAssetPropertiesTabFactory"

const FName FCustomAssetPropertiesTabFactory::TabFactoryID(TEXT("CustomAssetPropertiesTab"));

FCustomAssetPropertiesTabFactory::FCustomAssetPropertiesTabFactory(const TSharedPtr<FCustomAssetEditorApp>& InApp):
::FWorkflowTabFactory(TabFactoryID, InApp),
CurrentApp(InApp)
{
	CurrentApp          = InApp;
	TabLabel            = LOCTEXT("Properties", "Properties");
	ViewMenuDescription = LOCTEXT("ViewMenuDescription", "Displays a Properties view");
	ViewMenuTooltip     = LOCTEXT("ViewMenuTooltip", "Show the Properties view.");
}

TSharedRef<SWidget> FCustomAssetPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<FCustomAssetEditorApp> TmpApp = CurrentApp.Pin();
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args;
	Args.bAllowSearch                  = false;   // 是否显示右上角的搜索框
	Args.bHideSelectionTip             = true;    // 是否隐藏顶部的“当前选择提示条（如：“选中了 1 个对象”）
	Args.bLockable                     = true;    // 是否显示“锁定按钮”，锁定后不会随选择自动更新
	Args.bSearchInitialKeyFocus        = true;    // 是否初始时把键盘焦点给搜索框
	Args.bUpdatesFromSelection         = false;   // 是否自动根据编辑器中的选择对象更新显示内容
	Args.NotifyHook                    = nullptr; // 用于响应属性值更改（Undo/Redo、事务系统等）
	Args.bShowOptions                  = true;    // 是否显示面板右上角的设置按钮（小齿轮）
	Args.bShowModifiedPropertiesOption = false;   // 是否显示“仅查看已修改属性”选项（用来只看已改动的属性）
	Args.bShowScrollBar                = true;    // 是否显示垂直滚动条

	TSharedPtr<IDetailsView> DetailsView = PropertyEditor.CreateDetailView(Args);
	DetailsView->SetObject(TmpApp->GetCurrentCustomAsset());

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		.HAlign(HAlign_Fill)
		[
			DetailsView.ToSharedRef()
		];

}

FText FCustomAssetPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText(LOCTEXT("CustomTabTestToolTipText", "A primary view for doing primary things!"));
}

FTabSpawnerEntry& FCustomAssetPropertiesTabFactory::RegisterTabSpawner(TSharedRef<FTabManager> TabManager,
                                                                    const FApplicationMode* CurrentApplicationMode)
const { return FWorkflowTabFactory::RegisterTabSpawner(TabManager, CurrentApplicationMode); }

TSharedRef<SDockTab> FCustomAssetPropertiesTabFactory::SpawnTab(const FWorkflowTabSpawnInfo& Info) const
{
	return FWorkflowTabFactory::SpawnTab(Info);
}


#undef LOCTEXT_NAMESPACE
