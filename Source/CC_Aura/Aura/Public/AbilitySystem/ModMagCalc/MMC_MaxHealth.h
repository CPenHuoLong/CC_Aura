// cccc

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class CC_AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxHealth();

	//自定义公式计算,根据GE的 Spec（包含等级、捕获的属性、上下文等）计算最终的数值。
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	//告诉 GAS：在执行公式时，需要捕获哪个属性（比如 Vigor），从谁身上捕获（Source 或 Target），什么时候捕获（快照 or 实时）。
	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
};
