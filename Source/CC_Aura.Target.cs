// cccc

using UnrealBuildTool;
using System.Collections.Generic;

public class CC_AuraTarget : TargetRules
{
	public CC_AuraTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "CC_Aura" } );
	}
}
