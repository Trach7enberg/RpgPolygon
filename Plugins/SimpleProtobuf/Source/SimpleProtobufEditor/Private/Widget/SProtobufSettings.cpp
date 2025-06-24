// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "Widget/SProtobufSettings.h"
#include "Widgets/Layout/SScrollBox.h"
#include "UObject/SimpleProtobufSettings.h"
#include "Misc/FileHelper.h"
#include "Json/SimpleProtobufJson.h"

#define LOCTEXT_NAMESPACE "SProtobufSettings"

void SProtobufSettings::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
		DetailsViewArgs.bShowPropertyMatrixButton = false;
	}

	TSharedPtr<class IDetailsView> ConfigPanel = PropertyModule.CreateDetailView(DetailsViewArgs);
	TArray<UObject*> SourceObjects;
	
	if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
	{
		InSettings->LoadObjectStorageConfig();

		SourceObjects.Add(InSettings);
	}

	ConfigPanel->SetObjects(SourceObjects);

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SNew(SScrollBox)
			.Orientation(Orient_Vertical)

			+ SScrollBox::Slot()
			[
				ConfigPanel.ToSharedRef()
			]		
		]

		+ SVerticalBox::Slot()
		.FillHeight(1.f)	
		.AutoHeight()
		[
			SNew(SButton)
			.Text(LOCTEXT("ProtobufCreateConfig", "Create Proto Config"))
			.HAlign(HAlign_Center)
			.OnClicked(this, &SProtobufSettings::CreateConfig)
			.ToolTipText(LOCTEXT("ProtobufCreateProtoTip", "Create Proto Config."))
		]
	];
}

FReply SProtobufSettings::CreateConfig()
{
	if (USimpleProtobufSettings* InInstallInfo = GetMutableDefault<USimpleProtobufSettings>())
	{
		if (!InInstallInfo->NewConfigName.IsEmpty())
		{
			if (!InInstallInfo->ProtoNames.Contains(InInstallInfo->NewConfigName))
			{
				InInstallInfo->ProtoNames.Add(InInstallInfo->NewConfigName);

				//设置当前所选择的配置
				InInstallInfo->CurrentSelected = InInstallInfo->NewConfigName;

				//存储配置
				InInstallInfo->SaveObjectStorageConfig();

				//清空为下一次创建而准备
				InInstallInfo->NewConfigName = TEXT("");

				//更新其他UI
				OnResetComboBoxSelectDelegate.Broadcast();

				FMessageDialog::Open(
					EAppMsgType::Ok,
					LOCTEXT("SProtobufCompileToProtoNameCreated", "Name created successfully."));
			}
			else
			{
				FMessageDialog::Open(
					EAppMsgType::Ok,
					LOCTEXT("SProtobufCompileToProtoName", "Name already exists."));
			}
		}
		else
		{
			FMessageDialog::Open(
				EAppMsgType::Ok,
				LOCTEXT("SProtobufCompileToProtoNoName", "NewConfigName Cannot be empty."));
		}		
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE