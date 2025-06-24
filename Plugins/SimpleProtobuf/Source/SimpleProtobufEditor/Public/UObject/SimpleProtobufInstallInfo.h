// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SimpleProtobufInfo.h"
#include "SimpleProtobufInstallInfo.generated.h"

UCLASS(config = SimpleProtobufInstall)
class SIMPLEPROTOBUFEDITOR_API USimpleProtobufInstallInfo :public USimpleProtobufObject
{
	GENERATED_BODY()

public:
	USimpleProtobufInstallInfo();

	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Install", meta = (ToolTip = "Output C++ file location."))
	FDirectoryPath GoogleRZPath;
};