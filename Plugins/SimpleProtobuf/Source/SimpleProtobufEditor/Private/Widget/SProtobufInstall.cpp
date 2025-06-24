// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "Widget/SProtobufInstall.h"
#include "PropertyEditorModule.h"
#include "Widgets/Layout/SScrollBox.h"
#include "UObject/SimpleProtobufInstallInfo.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Json/SimpleProtobufJson.h"
#include "UObject/SimpleProtobufSettings.h"
#include "SimpleProtobufEditorMacro.h"

#define LOCTEXT_NAMESPACE "SProtobufInstall"

void SProtobufInstall::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
		DetailsViewArgs.bShowPropertyMatrixButton = false;
	}

	ResetFromConfig();

	TSharedPtr<class IDetailsView> ConfigPanel = PropertyModule.CreateDetailView(DetailsViewArgs);
	TArray<UObject*> SourceObjects;
	{
		SourceObjects.Add(GetMutableDefault<USimpleProtobufInstallInfo>());
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
				BuildCombaBoxSelected()
			]

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
			.Text(LOCTEXT("ProtobufInstall", "Install"))
			.HAlign(HAlign_Center)
			.OnClicked(this, &SProtobufInstall::Install)
			.ToolTipText(LOCTEXT("ProtobufInstallTip", "Can Install code."))
		]
	];
}

void SProtobufInstall::ResetFromConfig()
{
	FString JsonString;
	if (auto SimpleProtobufPath = IPluginManager::Get().FindPlugin("SimpleProtobuf"))
	{
		if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
		{
			FString ProtoCommadPath = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / COMMANDSCRIPTPROTOBUF_INSTALL(InSettings->CurrentSelected));

			if (FFileHelper::LoadFileToString(JsonString, *ProtoCommadPath))
			{
				if (USimpleProtobufInstallInfo *InInstallInfo = GetMutableDefault<USimpleProtobufInstallInfo>())
				{
					InInstallInfo->ResetProtobuf();

					SimpleProtobufJson::Deserialize(JsonString,InInstallInfo);
				}
			}
		}
	}
}

void SProtobufInstall::SetNewSubjectName(FName SubjectName)
{
	SProtobufStringArrayConfig::SetNewSubjectName(SubjectName);

	ResetFromConfig();
}

FReply SProtobufInstall::Install()
{
	if (USimpleProtobufInstallInfo* InInstallInfo = GetMutableDefault<USimpleProtobufInstallInfo>())
	{
		InInstallInfo->SaveObjectStorageConfig();

		FString JsonString;
		SimpleProtobufJson::Serialize(InInstallInfo, JsonString);

		if (auto SimpleProtobufPath = IPluginManager::Get().FindPlugin("SimpleProtobuf"))
		{
			if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
			{
				FString ProtoCommadPath = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / COMMANDSCRIPTPROTOBUF_INSTALL(InSettings->CurrentSelected));

				if (FFileHelper::SaveStringToFile(JsonString, *ProtoCommadPath))
				{
					FString StartProtobufCompileBat = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / STARTPROTOBUFINSTALL(InSettings->CurrentSelected));
					BuildBat(InSettings->CurrentSelected, StartProtobufCompileBat);

					int32 ReturnValue = INDEX_NONE;
					if (!FPlatformProcess::ExecElevatedProcess(*StartProtobufCompileBat, nullptr, &ReturnValue))
					{
						FMessageDialog::Open(
							EAppMsgType::Ok,
							LOCTEXT("SProtobufCompileToProtoToInstallError", "UE C++ Install to proto Error."));
					}
					else
					{
						FMessageDialog::Open(
							EAppMsgType::Ok,
							LOCTEXT("SProtobufCompileToProtoToInstall", "UE C++ Install to proto Success."));
					}

					DestroyBat(StartProtobufCompileBat);
				}
			}
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE