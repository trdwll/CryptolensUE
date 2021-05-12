// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class Cryptolens : ModuleRules
{
	public Cryptolens(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "Cryptolens.lib"));

			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
        }
	}
}
