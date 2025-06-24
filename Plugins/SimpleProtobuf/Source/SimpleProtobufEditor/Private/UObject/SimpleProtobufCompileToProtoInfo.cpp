// Copyright (C) RenZhai.2021.All Rights Reserved.

#include "UObject/SimpleProtobufCompileToProtoInfo.h"

USimpleProtobufCompileToProtoInfo::USimpleProtobufCompileToProtoInfo()
	:Super()
{
	MetaTag = TEXT("Proto");
	GenerateProtoFilename = TEXT("ProtoCode");
}

void USimpleProtobufCompileToProtoInfo::ResetProtobuf()
{
	ImportProtoFile.Empty();
	GenerateProtoPaths.Empty();
}
