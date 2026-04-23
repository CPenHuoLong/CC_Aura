// cccc


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//获取 Source（施法者）和 Target（受击者）的标签
	const FGameplayTagContainer* SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();

	//计算属性时要考虑哪些标签,哪些 GE 的条件应该生效
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;

	//捕获属性：Vigor
	float Intelligence=0.f;
	GetCapturedAttributeMagnitude(IntDef,Spec,EvaluateParameters,Intelligence);
	//防止负数
	Intelligence=FMath::Max<float>(Intelligence,0.f);

	//获取玩家等级
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel=CombatInterface->GetPlayerLevel();
	
	return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}
