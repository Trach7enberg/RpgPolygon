// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;

public class RpgPolygon : ModuleRules
{
	public RpgPolygon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
		PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
		PublicDefinitions.Add("GOOGLE_PROTOBUF_CMAKE_BUILD");

		PublicIncludePaths.AddRange(new string[]
		{
			"RpgPolygon/ThirdParty",
			"RpgPolygon/ThirdParty/Protobuf",
			"RpgPolygon/ThirdParty/GoogleProtobuf",
			"RpgPolygon/ThirdParty/GoogleProtobuf/Source",
		});

		PublicDependencyModuleNames.AddRange(new String[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"EnhancedInput",
				"UMG",
				"Slate",
				"SlateCore",
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"NavigationSystem",
				"Niagara",
				"MotionWarping",
				"AIModule",
				"ModelViewViewModel",
				"AnimGraphRuntime",
				"CustomAssetEditorRuntime"
			}
		);

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.AddRange(new String[]
			{
				"CustomAssetEditor"
			});
		}

		PrivateDependencyModuleNames.AddRange(new string[]
		{
		});

		// protobuf begin
		ShadowVariableWarningLevel = WarningLevel.Off;

		bEnableUndefinedIdentifierWarnings = false;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			bEnableExceptions = true;
		}


		// protobuf end

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}