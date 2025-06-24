// Garrett Gan All Right Reserved


#include "Core/CustomAssetAction.h"

#include "Core/CustomAsset.h"
#include "Core/CustomAssetEditorApp.h"


FCustomAssetAction::FCustomAssetAction(EAssetTypeCategories::Type InAssetCategory): _AssetCategory(InAssetCategory) {}

FText FCustomAssetAction::GetName() const { return NSLOCTEXT("CustomAssetAction", "MyCustomAsset", "My Custom Asset"); }
FColor FCustomAssetAction::GetTypeColor() const { return FColor::White; }

UClass* FCustomAssetAction::GetSupportedClass() const { return UCustomAsset::StaticClass(); }

void FCustomAssetAction::OpenAssetEditor(const TArray<UObject*>&  InObjects,
                                         TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const auto InMode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (const auto Obj : InObjects)
	{
		const auto CustomAsset = Cast<UCustomAsset>(Obj);
		if (!CustomAsset) { continue; }
		const TSharedRef<FCustomAssetEditorApp> Editor(new FCustomAssetEditorApp());
		Editor->InitEditor(InMode, EditWithinLevelEditor, CustomAsset);
	}
}

uint32 FCustomAssetAction::GetCategories() { return _AssetCategory; }
