// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "UObject/SimpleProtobufBase.h"
#include "SimpleProtobufSettings.generated.h"

UCLASS(config = SimpleProtobufSettings)
class SIMPLEPROTOBUFEDITOR_API USimpleProtobufSettings :public USimpleProtobufBase
{
	GENERATED_BODY()

public:
	USimpleProtobufSettings();

	UPROPERTY(config,VisibleAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	TArray<FString> ProtoNames;

	UPROPERTY(config,VisibleAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FString CurrentSelected;

	UPROPERTY(config,EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FString NewConfigName;
};