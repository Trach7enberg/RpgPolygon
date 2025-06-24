// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "SimpleProtobufEditor.h"
#include "SimpleProtobufEditorStyle.h"
#include "SimpleProtobufEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "ISettingsModule.h"
#include "UObject/SimpleProtobufInfo.h"
#include "EditorStyleSet.h"
#include "Widgets/Images/SImage.h"
#include "Widget/SProtobufCompile.h"
#include "Widget/SProtobufInstall.h"
#include "Widget/SProtobufSettings.h"
#include "Widget/SProtobufCompileToProto.h"
#include "Widget/SProtobufBytesConversion.h"
#include "UObject/SimpleProtobufSettings.h"
#include "UObject/SimpleProtobufBytesConversion.h"

static const FName SimpleProtobufEditorTabName("SimpleProtobufEditor");

#define LOCTEXT_NAMESPACE "FSimpleProtobufEditorModule"

//安装和编译
struct FSimpleProtobufEditorTable
{
	static const FName ProtobufInstall;
	static const FName ProtobufCompile;
	static const FName ProtobufSettings;
	static const FName ProtobufBytesConversion;
	static const FName ProtobufCompileToProto;
};

const FName FSimpleProtobufEditorTable::ProtobufInstall = TEXT("ProtobufInstall");
const FName FSimpleProtobufEditorTable::ProtobufCompile = TEXT("ProtobufCompile");
const FName FSimpleProtobufEditorTable::ProtobufSettings = TEXT("ProtobufSettings");
const FName FSimpleProtobufEditorTable::ProtobufBytesConversion = TEXT("ProtobufBytesConversion");
const FName FSimpleProtobufEditorTable::ProtobufCompileToProto = TEXT("ProtobufCompileToProto");

void FSimpleProtobufEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSimpleProtobufEditorStyle::Initialize();
	FSimpleProtobufEditorStyle::ReloadTextures();

	FSimpleProtobufEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSimpleProtobufEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSimpleProtobufEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSimpleProtobufEditorModule::RegisterMenus));

	//注册到projectsetting
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>(TEXT("Settings")))
	{
		SettingsModule->RegisterSettings("Project","Protobuf","ProtobufSettings",
			LOCTEXT("ProtobufSettings", "Protobuf Settings"),
			LOCTEXT("ProtobufSettingsDescription", "Mainly used to generate c++ protocol files."),
			GetMutableDefault<USimpleProtobufObject>());
	}
}

void FSimpleProtobufEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSimpleProtobufEditorStyle::Shutdown();

	FSimpleProtobufEditorCommands::Unregister();
}

void FSimpleProtobufEditorModule::PluginButtonClicked()
{
	InitLayout();
}

void FSimpleProtobufEditorModule::InitLayout()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FSimpleProtobufEditorTable::ProtobufInstall);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FSimpleProtobufEditorTable::ProtobufCompile);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FSimpleProtobufEditorTable::ProtobufInstall, FOnSpawnTab::CreateRaw(this, &FSimpleProtobufEditorModule::SpawnTab_ProtobufInstall))
		.SetDisplayName(LOCTEXT("SimpleProtobufEditorTable—ProtobufInstall", "Install"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FSimpleProtobufEditorTable::ProtobufCompile, FOnSpawnTab::CreateRaw(this, &FSimpleProtobufEditorModule::SpawnTab_ProtobufCompile))
		.SetDisplayName(LOCTEXT("SimpleProtobufEditorTable—ProtobufCompile", "CompileC++"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FSimpleProtobufEditorTable::ProtobufCompileToProto, FOnSpawnTab::CreateRaw(this, &FSimpleProtobufEditorModule::SpawnTab_ProtobufCompileToProto))
		.SetDisplayName(LOCTEXT("SimpleProtobufEditorTable—ProtobufCompileToProto", "CompileToProto"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FSimpleProtobufEditorTable::ProtobufSettings, FOnSpawnTab::CreateRaw(this, &FSimpleProtobufEditorModule::SpawnTab_ProtobufSettings))
		.SetDisplayName(LOCTEXT("SimpleProtobufEditorTable—ProtobufSettings", "Settings"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FSimpleProtobufEditorTable::ProtobufBytesConversion, FOnSpawnTab::CreateRaw(this, &FSimpleProtobufEditorModule::SpawnTab_ProtobufBytesConversionSettings))
		.SetDisplayName(LOCTEXT("SimpleProtobufEditorTable—BytesConversionSettings", "BytesConversion"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Simple_Protobuf_Layout")
	->AddArea
	(
		FTabManager::NewArea(800,800)

		->Split
		(
			FTabManager::NewStack()		
			->AddTab(FSimpleProtobufEditorTable::ProtobufInstall, ETabState::OpenedTab)
			->AddTab(FSimpleProtobufEditorTable::ProtobufCompileToProto, ETabState::OpenedTab)
			->AddTab(FSimpleProtobufEditorTable::ProtobufCompile, ETabState::OpenedTab)
			->AddTab(FSimpleProtobufEditorTable::ProtobufBytesConversion, ETabState::OpenedTab)
			->AddTab(FSimpleProtobufEditorTable::ProtobufSettings, ETabState::OpenedTab)
		)
	);

	FGlobalTabmanager::Get()->RestoreFrom(Layout, TSharedPtr<SWindow>());
}

void FSimpleProtobufEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FSimpleProtobufEditorCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSimpleProtobufEditorCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

TSharedRef<SDockTab> FSimpleProtobufEditorModule::SpawnTab_ProtobufInstall(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> NewDockTab = SNew(SDockTab)
	.Icon(FEditorStyle::GetBrush("CurveAssetEditor.Tabs.Properties"))
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(0.0f)
		[
			SNew(SProtobufInstall)
		]
	];

	return NewDockTab;
}

TSharedRef<SDockTab> FSimpleProtobufEditorModule::SpawnTab_ProtobufCompile(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> NewDockTab = SNew(SDockTab)
	.Icon(FEditorStyle::GetBrush("CurveAssetEditor.Tabs.Properties"))
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(0.0f)
		[
			SNew(SProtobufCompile)
		]
	];

	return NewDockTab;
}

TSharedRef<SDockTab> FSimpleProtobufEditorModule::SpawnTab_ProtobufCompileToProto(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> NewDockTab = SNew(SDockTab)
	.Icon(FEditorStyle::GetBrush("CurveAssetEditor.Tabs.Properties"))
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(0.0f)
		[
			SNew(SProtobufCompileToProto)
		]
	];

	return NewDockTab;
}

TSharedRef<SDockTab> FSimpleProtobufEditorModule::SpawnTab_ProtobufBytesConversionSettings(const FSpawnTabArgs& Args)
{
TSharedRef<SDockTab> NewDockTab = SNew(SDockTab)
	.Icon(FEditorStyle::GetBrush("CurveAssetEditor.Tabs.Properties"))
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(0.0f)
		[
			SNew(SProtobufBytesConversion)
		]
	];

	return NewDockTab;
}

TSharedRef<SDockTab> FSimpleProtobufEditorModule::SpawnTab_ProtobufSettings(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> NewDockTab = SNew(SDockTab)
	.Icon(FEditorStyle::GetBrush("CurveAssetEditor.Tabs.Properties"))
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(0.0f)
		[
			SNew(SProtobufSettings)
		]
	];

	return NewDockTab;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleProtobufEditorModule, SimpleProtobufEditor)