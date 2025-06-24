// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SimpleProtobufInfo.h"

namespace SimpleProtobufJson
{
	void Serialize(USimpleProtobufObject* InObject,FString &OutJsonString);
	void Deserialize(const FString& InJsonString, USimpleProtobufObject* InObject);
}