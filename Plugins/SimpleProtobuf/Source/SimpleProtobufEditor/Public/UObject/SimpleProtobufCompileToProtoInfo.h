// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SimpleProtobufBase.h"
#include "SimpleProtobufCompileToProtoInfo.generated.h"

UCLASS(config = SimpleProtobufCompileToProtoInfo)
class SIMPLEPROTOBUFEDITOR_API USimpleProtobufCompileToProtoInfo :public USimpleProtobufBase
{
	GENERATED_BODY()

public:
	USimpleProtobufCompileToProtoInfo();

	//配置
	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	TArray<FDirectoryPath> GenerateProtoPaths;

	//暂时不支持 因为逻辑太复杂 没有精力研究依赖生成 敬请谅解...
//	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	TArray<FString> ImportProtoFile;

	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FString GenerateProtoFilename;

	UPROPERTY(config, VisibleAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FString MetaTag;

public:
	virtual void ResetProtobuf();
};