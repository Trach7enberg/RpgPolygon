// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SimpleProtobufInfo.h"
#include "SimpleProtobufCompileInfo.generated.h"

UCLASS(config = SimpleProtobufCompileInfo)
class SIMPLEPROTOBUFEDITOR_API USimpleProtobufCompileInfo :public USimpleProtobufObject
{
	GENERATED_BODY()

public:
	USimpleProtobufCompileInfo();
};