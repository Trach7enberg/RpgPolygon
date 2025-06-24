// Copyright (C) RenZhai.2021.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widget/SProtobufStringArrayConfig.h"

class SProtobufSettings :public SProtobufStringArrayConfig
{
public:
	SLATE_BEGIN_ARGS(SProtobufSettings)
		{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

public:
	FReply CreateConfig();
};