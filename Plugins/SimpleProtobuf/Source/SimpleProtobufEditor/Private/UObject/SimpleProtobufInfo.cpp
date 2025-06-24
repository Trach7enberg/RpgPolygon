// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "UObject/SimpleProtobufInfo.h"
#include "Interfaces/IPluginManager.h"

USimpleProtobufObject::USimpleProtobufObject()
{
	bPause = false;

	if (auto SimpleProtobufPath = IPluginManager::Get().FindPlugin("SimpleProtobuf"))
	{
		ProtoExe.FilePath = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / TEXT("RENZHAIAutomationTool/Engine/Binaries/Win64/protoc.exe"));
	}
}

void USimpleProtobufObject::ResetProtobuf()
{
	Maps.Empty();
}
