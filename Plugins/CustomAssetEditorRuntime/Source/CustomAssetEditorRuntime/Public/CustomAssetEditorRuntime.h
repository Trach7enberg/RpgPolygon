// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY_STATIC(CustomAssetEditorRuntimeLog, All, All);

namespace CustomAssetEditorRuntime
{
	static void Print(
		const FString&            Msg             = "",
		const float               InTimeToDisplay = 4.f,
		const int32               InKey           = -1,
		const FColor&             Color           = FColor::MakeRandomColor(),
		const ELogVerbosity::Type InLogLevel      = ELogVerbosity::Warning)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, InTimeToDisplay, Color, Msg);
			switch (InLogLevel)
			{
				case ELogVerbosity::Error:
					UE_LOG(CustomAssetEditorRuntimeLog, Error, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(CustomAssetEditorRuntimeLog, Warning, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(CustomAssetEditorRuntimeLog, Log, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				default:
					break;
			}
		}
	}
}


class FCustomAssetEditorRuntimeModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
