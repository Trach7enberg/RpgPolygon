// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SimpleProtobufBase.h"
#include "SimpleProtobufInfo.generated.h"

UCLASS(config = SimpleProtobufObject)
class SIMPLEPROTOBUFEDITOR_API USimpleProtobufObject :public USimpleProtobufBase
{
	GENERATED_BODY()

public:
	USimpleProtobufObject();

	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	FFilePath ProtoExe;

	//是否暂停
	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	bool bPause;

	//配置
	UPROPERTY(config, EditAnywhere, Category = "Protobuf|Common", meta = (ToolTip = "Output C++ file location."))
	TArray<FProtobufMap> Maps;

public:
	virtual void ResetProtobuf();
};