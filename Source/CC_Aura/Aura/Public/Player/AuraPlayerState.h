// cccc

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class CC_AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

protected:

	//能力系统组件  管理角色的技能（Gameplay Abilities） 管理属性（AttributeSets）管理效果（Gameplay Effects）处理技能冷却、消耗、触发条件等逻辑
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	//用来定义和存储角色的数值属性 生命值 (Health) 魔法值 (Mana) 攻击力、防御力等
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
