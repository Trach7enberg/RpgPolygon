// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "Widget/SProtobufCompileToProto.h"
#include "PropertyEditorModule.h"
#include "Widgets/Layout/SScrollBox.h"
#include "UObject/SimpleProtobufCompileToProtoInfo.h"
#include "Json/SimpleProtobufJson.h"
#include "Misc/FileHelper.h"
#include "SimpleProtobufBPLibrary.h"
#include "Misc/MessageDialog.h"
#include "UObject/SimpleProtobufSettings.h"

#define LOCTEXT_NAMESPACE "SProtobufCompileToProto"

void SProtobufCompileToProto::Construct(const FArguments& InArgs)
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
		SourceObjects.Add(GetMutableDefault<USimpleProtobufCompileToProtoInfo>());
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
			.Text(LOCTEXT("ProtobufCompileToProto", "Compile"))
			.HAlign(HAlign_Center)
			.OnClicked(this, &SProtobufCompileToProto::Compile)
			.ToolTipText(LOCTEXT("ProtobufCompileProtoTip", "Can compile code to proto."))
		]
	];
}

void SProtobufCompileToProto::ResetFromConfig()
{
	if (USimpleProtobufCompileToProtoInfo* InCompileInfo = GetMutableDefault<USimpleProtobufCompileToProtoInfo>())
	{
		if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
		{
			InCompileInfo->LoadObjectStorageConfig(InSettings->CurrentSelected);
		}
	}
}

void SProtobufCompileToProto::SetNewSubjectName(FName SubjectName)
{
	SProtobufStringArrayConfig::SetNewSubjectName(SubjectName);

	ResetFromConfig();
}

FReply SProtobufCompileToProto::Compile()
{
	if (USimpleProtobufCompileToProtoInfo* InCompileInfo = GetMutableDefault<USimpleProtobufCompileToProtoInfo>())
	{
		InCompileInfo->SaveObjectStorageConfig();

		if (InCompileInfo->GenerateProtoPaths.Num() > 0 && 
			!InCompileInfo->GenerateProtoFilename.IsEmpty() &&
			!InCompileInfo->MetaTag.IsEmpty())
		{
			TArray<FString> GenerateProtoPaths;
			for (auto &Tmp : InCompileInfo->GenerateProtoPaths)
			{
				GenerateProtoPaths.Add(Tmp.Path);
			}

			if (!USimpleProtobufBPLibrary::GenerateProtoCode(
				GenerateProtoPaths,
				InCompileInfo->ImportProtoFile,
				InCompileInfo->GenerateProtoFilename,
				InCompileInfo->MetaTag))
			{
				FMessageDialog::Open(
					EAppMsgType::Ok,
					LOCTEXT("SProtobufCompileToProtoToError", "Generation failed, check for unsupported types."));
			}
			else
			{
				if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
				{
					InCompileInfo->SaveObjectStorageConfig(InSettings->CurrentSelected);
				}

				FMessageDialog::Open(
					EAppMsgType::Ok,
					LOCTEXT("SProtobufCompileToProtoToSuccess", "UE C++ compile to proto Success."));
			}
		}
		else
		{
			FMessageDialog::Open(
				EAppMsgType::Ok,
				LOCTEXT("SProtobufCompileToProtoToError1", "Compilation failed, please check if the generated proto path is empty or if the generated file name is empty, metatag cannot be empty."));
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE