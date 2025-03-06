// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ue5flecs : ModuleRules
{
	public ue5flecs(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "FlecsLibrary" });
        PrivateDependencyModuleNames.AddRange(new string[] { "FlecsLibrary" });
    }
}
