// Copyright (C) RenZhai.2021.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SComboBox.h"

class SProtobufStringArrayConfig :public SCompoundWidget
{
public:
	~SProtobufStringArrayConfig();
	SProtobufStringArrayConfig();

public:
	virtual TSharedRef<SComboBox<TSharedPtr<FString>>> BuildCombaBoxSelected();

public:
	void StartBind();
	void EndBind();

	void BuildBat(const FString &InSelected,const FString &InSavePath,bool bPause = false);
	void DestroyBat(const FString& InSavePath);

public:
	//ComboButton
	virtual TSharedRef<SWidget> MakeComboButtonItemWidget(TSharedPtr<FString> StringItem);
	virtual void OnSelectionChanged(TSharedPtr<FString> StringItem, ESelectInfo::Type SelectInfo);
	virtual FText GetSelectedSubjectName() const;
	virtual void OnSubjectNameComboBoxOpened();

	virtual void SetNewSubjectName(FName SubjectName);
	virtual void RefreshSubjectNames();

	//ComboBox
protected:
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBoxSelect;
	TArray<TSharedPtr<FString>> SubjectNames;
	TSharedPtr<FString> CurrentSelectedSubjectName;
	FDelegateHandle DelegateHandle;
};