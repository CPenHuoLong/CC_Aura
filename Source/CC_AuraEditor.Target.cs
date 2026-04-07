// cccc

using UnrealBuildTool;
using System.Collections.Generic;

public class CC_AuraEditorTarget : TargetRules
{
	public CC_AuraEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "CC_Aura" } );
	}
}
