// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "Widget/SProtobufBytesConversion.h"
#include "PropertyEditorModule.h"
#include "Widgets/Layout/SScrollBox.h"
#include "UObject/SimpleProtobufCompileInfo.h"
#include "Json/SimpleProtobufJson.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "SimpleProtobufEditorMacro.h"
#include "UObject/SimpleProtobufBytesConversion.h"
#include "SimpleProtobufBPLibrary.h"

#define LOCTEXT_NAMESPACE "SProtobufCompile"

void SProtobufBytesConversion::Construct(const FArguments& InArgs)
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
		SourceObjects.Add(GetMutableDefault<USimpleProtobufBytesConversion>());
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
			.Text(LOCTEXT("ProtobufConversion", "Conversion"))
			.HAlign(HAlign_Center)
			.OnClicked(this, &SProtobufBytesConversion::Conversion)
			.ToolTipText(LOCTEXT("ProtobufConversionTip", "Can Conversion code."))
		]
	];
}

void SProtobufBytesConversion::SetNewSubjectName(FName SubjectName)
{
	SProtobufStringArrayConfig::SetNewSubjectName(SubjectName);

	ResetFromConfig();
}

void SProtobufBytesConversion::ResetFromConfig()
{
	
}

FReply SProtobufBytesConversion::Conversion()
{
	if (USimpleProtobufBytesConversion* InCompileInfo = GetMutableDefault<USimpleProtobufBytesConversion>())
	{
		InCompileInfo->SaveObjectStorageConfig();
		
		if (USimpleProtobufBPLibrary::GenerateBytesConversion(
			InCompileInfo->CPPIncludePaths,
			InCompileInfo->APIName,
			InCompileInfo->Filename,
			InCompileInfo->GenerateBytesConversionCodeHPaths.Path,
			InCompileInfo->GenerateBytesConversionCodeCPPPaths.Path,
			InCompileInfo->ProtoCode))
		{
			FMessageDialog::Open(
				EAppMsgType::Ok,
				LOCTEXT("SProtobufBytesConversion", "BytesConversion Success."));
		}
		else
		{
			FMessageDialog::Open(
				EAppMsgType::Ok,
				LOCTEXT("SProtobufBytesConversion-false", "BytesConversion fail."));
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE