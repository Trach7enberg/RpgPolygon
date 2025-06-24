// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "Widget/SProtobufCompile.h"
#include "PropertyEditorModule.h"
#include "Widgets/Layout/SScrollBox.h"
#include "UObject/SimpleProtobufCompileInfo.h"
#include "Json/SimpleProtobufJson.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "SimpleProtobufEditorMacro.h"
#include "UObject/SimpleProtobufSettings.h"

#define LOCTEXT_NAMESPACE "SProtobufCompile"

void SProtobufCompile::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked< FPropertyEditorModule >("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
		DetailsViewArgs.bShowPropertyMatrixButton = false;
	}

	ResetFromConfig();

	TSharedPtr<class IDetailsView> ConfigPanel = PropertyModule.CreateDetailView(DetailsViewArgs);
	TArray<UObject*> SourceObjects;
	{
		SourceObjects.Add(GetMutableDefault<USimpleProtobufCompileInfo>());
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
			.Text(LOCTEXT("ProtobufCompile", "Compile"))
			.HAlign(HAlign_Center)
			.OnClicked(this, &SProtobufCompile::Compile)
			.ToolTipText(LOCTEXT("ProtobufCompileTip", "Can compile code."))
		]
	];
}

void SProtobufCompile::SetNewSubjectName(FName SubjectName)
{
	SProtobufStringArrayConfig::SetNewSubjectName(SubjectName);

	ResetFromConfig();
}

void SProtobufCompile::ResetFromConfig()
{
	FString JsonString;
	if (auto SimpleProtobufPath = IPluginManager::Get().FindPlugin("SimpleProtobuf"))
	{
		if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
		{
			FString ProtoCommadPath = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / COMMANDSCRIPTPROTOBUF_INSTALL(InSettings->CurrentSelected));

			if (FFileHelper::LoadFileToString(JsonString, *ProtoCommadPath))
			{
				if (USimpleProtobufCompileInfo *InCompileInfo = GetMutableDefault<USimpleProtobufCompileInfo>())
				{
					InCompileInfo->ResetProtobuf();

					SimpleProtobufJson::Deserialize(JsonString,InCompileInfo);
				}
			}
		}
	}
}

FReply SProtobufCompile::Compile()
{
	if (USimpleProtobufCompileInfo *InCompileInfo = GetMutableDefault<USimpleProtobufCompileInfo>())
	{
		InCompileInfo->SaveObjectStorageConfig();

		FString JsonString;
		SimpleProtobufJson::Serialize(InCompileInfo, JsonString);

		if (auto SimpleProtobufPath = IPluginManager::Get().FindPlugin("SimpleProtobuf"))
		{
			if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
			{ 
				FString ProtoCommadPath = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / COMMANDSCRIPTPROTOBUF_INSTALL(InSettings->CurrentSelected));

				if (FFileHelper::SaveStringToFile(JsonString, *ProtoCommadPath))
				{
					FString StartProtobufCompileBat = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / STARTPROTOBUFINSTALL(InSettings->CurrentSelected));
					BuildBat(InSettings->CurrentSelected, StartProtobufCompileBat, InCompileInfo->bPause);

					int32 ReturnValue = INDEX_NONE;
					if (!FPlatformProcess::ExecElevatedProcess(*StartProtobufCompileBat, nullptr, &ReturnValue))
					{
						FMessageDialog::Open(
							EAppMsgType::Ok,
							LOCTEXT("SProtobufCompileError", "Compile Error."));
					}
					else
					{
						FMessageDialog::Open(
							EAppMsgType::Ok,
							LOCTEXT("SProtobufCompile", "Compile Success."));
					}

					DestroyBat(StartProtobufCompileBat);
				}
			}
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE