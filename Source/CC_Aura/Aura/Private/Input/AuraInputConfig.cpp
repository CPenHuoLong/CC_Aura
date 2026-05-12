// cccc


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,bool bLogNotFound) const
{
	for (const auto& Action: AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't Find AbilityInputAction for InputTag [%s],on InpuConfig [%s]"),*InputTag.ToString(),*GetNameSafe(this));
	}

	return nullptr;
}
