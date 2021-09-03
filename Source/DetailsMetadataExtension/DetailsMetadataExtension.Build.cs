// Copyright 2020-2021 Sheffer Online Services. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class DetailsMetadataExtension : ModuleRules
{
	public DetailsMetadataExtension(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Disable for Non-Developer builds
		//OptimizeCode = CodeOptimization.Never;

        PrivateDependencyModuleNames.AddRange(
	        new string[]
	        {
	        	"Core",
                "CoreUObject",
                "Slate",
                "SlateCore",
                "InputCore",
                "Engine",
                "UnrealEd",
                "KismetCompiler",
                "BlueprintGraph",
                "ControlRig",
                "ControlRigDeveloper",
                "Kismet",
                "EditorStyle",
                "ApplicationCore",
                "PropertyEditor",
                "PropertyPath",
	        }
        );
	}
}
