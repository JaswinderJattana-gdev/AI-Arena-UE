// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealAIArenaDemo : ModuleRules
{
	public UnrealAIArenaDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UnrealAIArenaDemo",
			"UnrealAIArenaDemo/Variant_Platforming",
			"UnrealAIArenaDemo/Variant_Platforming/Animation",
			"UnrealAIArenaDemo/Variant_Combat",
			"UnrealAIArenaDemo/Variant_Combat/AI",
			"UnrealAIArenaDemo/Variant_Combat/Animation",
			"UnrealAIArenaDemo/Variant_Combat/Gameplay",
			"UnrealAIArenaDemo/Variant_Combat/Interfaces",
			"UnrealAIArenaDemo/Variant_Combat/UI",
			"UnrealAIArenaDemo/Variant_SideScrolling",
			"UnrealAIArenaDemo/Variant_SideScrolling/AI",
			"UnrealAIArenaDemo/Variant_SideScrolling/Gameplay",
			"UnrealAIArenaDemo/Variant_SideScrolling/Interfaces",
			"UnrealAIArenaDemo/Variant_SideScrolling/UI"
		});
	}
}
