// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widget/SProtobufStringArrayConfig.h"

class SProtobufBytesConversion :public SProtobufStringArrayConfig
{
public:
	SLATE_BEGIN_ARGS(SProtobufBytesConversion)
		{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual void SetNewSubjectName(FName SubjectName);

	void ResetFromConfig();

	FReply Conversion();
};
