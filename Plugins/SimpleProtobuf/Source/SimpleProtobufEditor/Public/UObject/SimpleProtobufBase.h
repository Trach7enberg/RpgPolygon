// Copyright (C) RenZhai.2021.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SimpleProtobufEditorType.h"
#include "SimpleProtobufBase.generated.h"

UCLASS(config = SimpleProtobufBase)
class SIMPLEPROTOBUFEDITOR_API USimpleProtobufBase :public UObject
{
	GENERATED_BODY()

public:
	USimpleProtobufBase();

public:
	void SaveObjectStorageConfig(const FString &InConfigName = TEXT(""));
	void LoadObjectStorageConfig(const FString &InConfigName = TEXT(""));
};