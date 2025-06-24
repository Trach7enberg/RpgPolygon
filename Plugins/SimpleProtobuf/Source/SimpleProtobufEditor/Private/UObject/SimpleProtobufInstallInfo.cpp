// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "UObject/SimpleProtobufInstallInfo.h"
#include "Interfaces/IPluginManager.h"

USimpleProtobufInstallInfo::USimpleProtobufInstallInfo()
	:Super()
{
	if (auto SimpleProtobufPath = IPluginManager::Get().FindPlugin("SimpleProtobuf"))
	{
		GoogleRZPath.Path = FPaths::ConvertRelativePathToFull(SimpleProtobufPath->GetBaseDir() / TEXT("RENZHAIAutomationTool/Engine/Content/google.rz"));
	}
}
