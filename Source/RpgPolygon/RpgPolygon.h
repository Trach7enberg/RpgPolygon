// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/// 角色描边颜色-红色
#define CUSTOM_DEPTH_RED 250

/// 角色描边颜色-蓝色
#define CUSTOM_DEPTH_BLUE 251

/// 角色描边颜色-棕褐色
#define CUSTOM_DEPTH_TAN 252

/// 碰撞预设 射弹
#define COLLISION_PRESET_PROJECTILE FName("Projectile")

DEFINE_LOG_CATEGORY_STATIC(RpgPolyDebugLog, All, All);

namespace RpgPolyDebug
{
	static void Print(
		const FString&            Msg,
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
					UE_LOG(RpgPolyDebugLog, Error, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(RpgPolyDebugLog, Warning, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(RpgPolyDebugLog, Log, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				default:
					break;
			}
		}
	}
}
