// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EquipmentSystem : ModuleRules
{
    public EquipmentSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
            {"Core", "CoreUObject", "Engine", "InputCore", "UMG", "SpinePlugin", "ProceduralMeshComponent"});

        PrivateDependencyModuleNames.AddRange(new[] {"Slate", "SlateCore"});
    }
}