#include "Widget/SProtobufStringArrayConfig.h"
#include "UObject/SimpleProtobufSettings.h"
#include "Misc/FileHelper.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

#define  LOCTEXT_NAMESPACE "SProtobufStringArrayConfig"

SProtobufStringArrayConfig::~SProtobufStringArrayConfig()
{
	EndBind();
}

SProtobufStringArrayConfig::SProtobufStringArrayConfig()
{
	StartBind();
}

TSharedRef<SComboBox<TSharedPtr<FString>>> SProtobufStringArrayConfig::BuildCombaBoxSelected()
{
	ComboBoxSelect = SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&SubjectNames)
		.OnGenerateWidget(this, &SProtobufStringArrayConfig::MakeComboButtonItemWidget)
		.OnSelectionChanged(this, &SProtobufStringArrayConfig::OnSelectionChanged)
		.OnComboBoxOpening(this, &SProtobufStringArrayConfig::OnSubjectNameComboBoxOpened)
		[
			SNew(STextBlock)
				.Text(this, &SProtobufStringArrayConfig::GetSelectedSubjectName)
		];

	RefreshSubjectNames();

	return ComboBoxSelect.ToSharedRef();
}

void SProtobufStringArrayConfig::StartBind()
{
	DelegateHandle = OnResetComboBoxSelectDelegate.AddRaw(this,&SProtobufStringArrayConfig::RefreshSubjectNames);
}

void SProtobufStringArrayConfig::EndBind()
{
	OnResetComboBoxSelectDelegate.Remove(DelegateHandle);
}

void SProtobufStringArrayConfig::BuildBat(const FString& InSelected,const FString& InSavePath, bool bPause)
{
	TArray<FString> ContentString;
	ContentString.Add(TEXT("cd /d %~dp0"));
	ContentString.Add(FString::Printf(TEXT("start Engine/Binaries/Win64/RENZHAIAutomationTool.exe -CommandScript=CommandScriptProtobuf_%s"), *InSelected));
	if (bPause)
	{
		ContentString.Add(TEXT("pause"));
	}

	FFileHelper::SaveStringArrayToFile(ContentString,*InSavePath);
}

void SProtobufStringArrayConfig::DestroyBat(const FString& InSavePath)
{
	if (IFileManager::Get().Delete(*InSavePath))
	{

	}
}

TSharedRef<SWidget> SProtobufStringArrayConfig::MakeComboButtonItemWidget(TSharedPtr<FString> StringItem)
{
	return SNew(STextBlock)
		.Text(FText::FromString(*StringItem));
}

void SProtobufStringArrayConfig::OnSelectionChanged(TSharedPtr<FString> StringItem, ESelectInfo::Type SelectInfo)
{
	if (StringItem.IsValid())
	{
		SetNewSubjectName(FName(**StringItem));
	}
}

FText SProtobufStringArrayConfig::GetSelectedSubjectName() const
{
	return CurrentSelectedSubjectName.IsValid() ? FText::FromString(*CurrentSelectedSubjectName) : FText();
}

void SProtobufStringArrayConfig::OnSubjectNameComboBoxOpened()
{
	RefreshSubjectNames();
}

void SProtobufStringArrayConfig::SetNewSubjectName(FName SubjectName)
{
	CurrentSelectedSubjectName = MakeShareable(new FString(SubjectName.ToString()));

	if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
	{
		InSettings->CurrentSelected = *CurrentSelectedSubjectName;
	}
}

void SProtobufStringArrayConfig::RefreshSubjectNames()
{
	SubjectNames.Reset();

	if (USimpleProtobufSettings* InSettings = GetMutableDefault<USimpleProtobufSettings>())
	{
		for (const auto& SubjectName : InSettings->ProtoNames)
		{
			SubjectNames.Add(MakeShareable(new FString(SubjectName)));
		}

		//设置当前的名字'
		if (CurrentSelectedSubjectName.IsValid())
		{
			if (*CurrentSelectedSubjectName != InSettings->CurrentSelected)
			{
				CurrentSelectedSubjectName = MakeShareable(new FString(InSettings->CurrentSelected));
			}
		}
		else
		{
			CurrentSelectedSubjectName = MakeShareable(new FString(InSettings->CurrentSelected));
		}		
	}

	if (!SubjectNames.Find(CurrentSelectedSubjectName))
	{
		SubjectNames.Add(CurrentSelectedSubjectName);
	}

	if (ComboBoxSelect.IsValid())
	{
		ComboBoxSelect->RefreshOptions();
	}
}

#undef LOCTEXT_NAMESPACE

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif