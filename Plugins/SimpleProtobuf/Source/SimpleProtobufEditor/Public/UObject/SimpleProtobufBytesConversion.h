// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SimpleProtobufBase.h"
#include "SimpleProtobufBytesConversion.generated.h"

UCLASS(config = SimpleProtobufBytesConversion)
class SIMPLEPROTOBUFEDITOR_API USimpleProtobufBytesConversion :public USimpleProtobufBase
{
	GENERATED_BODY()

public:
	USimpleProtobufBytesConversion();

	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FString APIName;

	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FString Filename;

	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FString ProtoCode;

	//需要包含的头文件
	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	TArray<FString> CPPIncludePaths;

	//想要生成转换代码的.h路径
	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FDirectoryPath GenerateBytesConversionCodeHPaths;

	//想要生成转换代码的.cpp路径
	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FDirectoryPath GenerateBytesConversionCodeCPPPaths;
};