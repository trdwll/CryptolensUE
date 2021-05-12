// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CryptolensUE : ModuleRules
{
	public CryptolensUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "Cryptolens", "Projects", "CoreUObject" });
	}
}
