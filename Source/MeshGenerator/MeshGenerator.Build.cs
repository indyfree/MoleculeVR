// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using System;
using UnrealBuildTool;

public class MeshGenerator : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public MeshGenerator(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent" });

        PublicDependencyModuleNames.AddRange(new string[] { "ShaderCore", "RenderCore", "RHI",  "RuntimeMeshComponent" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "tinyply", "Libraries", "tinyply.lib"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "tinyply", "Includes"));

    }
}
