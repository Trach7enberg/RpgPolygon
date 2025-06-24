// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FSimpleProtobufEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
	void InitLayout();

private:
	void RegisterMenus();

private:
	TSharedRef<SDockTab> SpawnTab_ProtobufInstall(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_ProtobufCompile(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_ProtobufCompileToProto(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_ProtobufBytesConversionSettings(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_ProtobufSettings(const FSpawnTabArgs& Args);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
