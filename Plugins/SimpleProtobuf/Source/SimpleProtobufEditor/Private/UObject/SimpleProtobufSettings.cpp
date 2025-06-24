#include "UObject/SimpleProtobufSettings.h"

USimpleProtobufSettings::USimpleProtobufSettings()
{
	CurrentSelected = TEXT("NewProtoCodeName");

	ProtoNames.Add(CurrentSelected);
}
