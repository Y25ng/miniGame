// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MiniGame : ModuleRules
{
	public MiniGame( ReadOnlyTargetRules Target ) : base( Target )
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "NavigationSystem", "Sockets", "Networking" });
	}
}
