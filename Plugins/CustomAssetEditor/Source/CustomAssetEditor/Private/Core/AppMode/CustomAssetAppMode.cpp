// Garrett Gan All Right Reserved


#include "Core/AppMode/CustomAssetAppMode.h"
#include "Core/CustomAssetEditorApp.h"
#include "Core/TabFactory/CustomAssetPrimaryTabFactory.h"
#include "Core/TabFactory/FCustomAssetPropertiesTabFactory.h"

#define LOCTEXT_NAMESPACE "FCustomAssetAppMode"

const FName FCustomAssetAppMode::ModID(TEXT("CustomAssetAppMode"));
const FName FCustomAssetAppMode::TabLayoutName(TEXT("Custom Asset Editor v1.0"));

FCustomAssetAppMode::FCustomAssetAppMode(const TSharedRef<FCustomAssetEditorApp>& InApp)
: FApplicationMode(ModID)
{
	CurrentApp = InApp;
	CurrentTabSet.RegisterFactory(MakeShared<FCustomAssetPrimaryTabFactory>(InApp));
	CurrentTabSet.RegisterFactory(MakeShared<FCustomAssetPropertiesTabFactory>(InApp));

	// 设置这个自定义资产的布局模式
	TabLayout = FTabManager::NewLayout(FCustomAssetAppMode::TabLayoutName)
			->AddArea(
			          FTabManager::NewPrimaryArea()
			          ->SetOrientation(Orient_Horizontal)
			          ->Split(
			                  FTabManager::NewSplitter()
			                  ->SetOrientation(Orient_Horizontal)
			                  ->Split(FTabManager::NewStack()
			                          ->SetSizeCoefficient(.75f)
			                          ->AddTab(FCustomAssetPrimaryTabFactory::TabFactoryID, ETabState::OpenedTab)
			                         )
			                  ->Split(FTabManager::NewStack()
			                          ->SetSizeCoefficient(.25f)
			                          ->AddTab( FCustomAssetPrimaryTabFactory::TabFactoryID, ETabState::OpenedTab))
			                 )
			         );
}

void FCustomAssetAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	const TSharedPtr<FCustomAssetEditorApp> InApp = CurrentApp.Pin();
	InApp->PushTabFactories(CurrentTabSet);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FCustomAssetAppMode::PreDeactivateMode() { FApplicationMode::PreDeactivateMode(); }
void FCustomAssetAppMode::PostActivateMode() { FApplicationMode::PostActivateMode(); }

#undef LOCTEXT_NAMESPACE
