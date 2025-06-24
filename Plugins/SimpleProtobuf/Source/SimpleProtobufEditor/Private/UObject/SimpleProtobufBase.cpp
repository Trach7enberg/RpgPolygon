#include "UObject/SimpleProtobufBase.h"

USimpleProtobufBase::USimpleProtobufBase()
{

}

void USimpleProtobufBase::SaveObjectStorageConfig(const FString &InConfigName)
{
	FString ConfigName = InConfigName;
	if (InConfigName.IsEmpty())
	{
		ConfigName = GetClass()->ClassConfigName.ToString();
	}

	FString SettingsEditorConfigPath = FPaths::ProjectConfigDir() / TEXT("Default") + ConfigName + TEXT(".ini");

	SaveConfig(CPF_Config, *SettingsEditorConfigPath);
}

void USimpleProtobufBase::LoadObjectStorageConfig(const FString& InConfigName)
{
	FString ConfigName = InConfigName;
	if (InConfigName.IsEmpty())
	{
		ConfigName = GetClass()->ClassConfigName.ToString();
	}

	FString SettingsEditorConfigPath = FPaths::ProjectConfigDir() / TEXT("Default") + GetClass()->ClassConfigName.ToString() + TEXT(".ini");

	LoadConfig(GetClass(), *SettingsEditorConfigPath);
}