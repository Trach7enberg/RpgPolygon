// Garrett Gan All Right Reserved


#include "Core/TabFactory/CustomAssetPrimaryTabFactory.h"

#include "CustomAssetEditorRuntime.h"
#include "GraphEditor.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "Core/CustomAssetEditorApp.h"

#define LOCTEXT_NAMESPACE "CustomAssetPrimaryTabFactory"

const FName FCustomAssetPrimaryTabFactory::TabFactoryID(TEXT("CustomAssetPrimaryTab"));


FCustomAssetPrimaryTabFactory::FCustomAssetPrimaryTabFactory(const TSharedPtr<FCustomAssetEditorApp>& InApp):
::FWorkflowTabFactory(TabFactoryID, InApp),
CurrentApp(InApp)
{
	CurrentApp          = InApp;
	TabLabel            = LOCTEXT("Primary", "Primary");
	ViewMenuDescription = LOCTEXT("ViewMenuDescription", "Displays a primary view");
	ViewMenuTooltip     = LOCTEXT("ViewMenuTooltip", "Show the primary view.");
}

TSharedRef<SWidget> FCustomAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<FCustomAssetEditorApp> TmpApp = CurrentApp.Pin();
	
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		.HAlign(HAlign_Fill)
		[
			SNew(SGraphEditor)
			.IsEditable(true)
			.GraphToEdit(TmpApp->GetCurrentGraph())
		];
}

FText FCustomAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText(LOCTEXT("CustomTabTestToolTipText", "A primary view for doing primary things!"));
}

FTabSpawnerEntry& FCustomAssetPrimaryTabFactory::RegisterTabSpawner(TSharedRef<FTabManager> TabManager,
                                                                    const FApplicationMode* CurrentApplicationMode)
const { return FWorkflowTabFactory::RegisterTabSpawner(TabManager, CurrentApplicationMode); }

TSharedRef<SDockTab> FCustomAssetPrimaryTabFactory::SpawnTab(const FWorkflowTabSpawnInfo& Info) const
{
	return FWorkflowTabFactory::SpawnTab(Info);
}


#undef LOCTEXT_NAMESPACE
