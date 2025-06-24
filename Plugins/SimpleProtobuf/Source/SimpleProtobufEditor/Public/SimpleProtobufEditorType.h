// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleProtobufEditorType.generated.h"

extern FSimpleMulticastDelegate OnResetComboBoxSelectDelegate;

USTRUCT(BlueprintType)
struct SIMPLEPROTOBUFEDITOR_API FProtobufMap
{
	GENERATED_USTRUCT_BODY()

	FProtobufMap()
	{}

	UPROPERTY(config, EditAnywhere, Category = "Protobuf", meta = (ToolTip = "Output C++ file location."))
	FString Key;

	UPROPERTY(config, EditAnywhere, Category = "Protobuf", meta = (ToolTip = "Output C++ file location."))
	FString Value;
};