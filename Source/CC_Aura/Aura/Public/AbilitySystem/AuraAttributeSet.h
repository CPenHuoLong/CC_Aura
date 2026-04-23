// cccc

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

/**
 * 
 */
UCLASS()
class CC_AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	//告诉引擎：这个类里哪些成员变量需要在网络中同步，以及同步时的条件。
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//在某个属性的值即将被修改之前，给你一个机会去拦截和调整这个新值。
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//当GameplayEffect 已经成功执行并修改了属性之后，在这里处理后续逻辑。
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/*主要属性*/

	//力量
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength,Category="Primary Attributes")
	FGameplayAttributeData Strength;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);
	//智力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Intelligence,Category="Primary Attributes")
	FGameplayAttributeData Intelligence;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence);
	//韧性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Resilience,Category="Primary Attributes")
	FGameplayAttributeData Resilience;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience);
	//活力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Vigor,Category="Primary Attributes")
	FGameplayAttributeData Vigor;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor);

	/*次要属性*/
	
	//护甲
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor,Category="Secondary Attributes")
	FGameplayAttributeData Armor;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor);
	//护甲穿透
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorPenetration,Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration);
	//格挡几率
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BlockChance,Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance);
	//暴击率
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitChance,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChance);
	//暴击伤害
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitDamage,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage);
	//暴击抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitResistance,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance);
	//生命恢复速度
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthRegeneration,Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration);
	//法力回复速度
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ManaRegeneration,Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration);
	//最大生命值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);
	//最大法力值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);
	
	/*重要属性*/

	//这个属性会在网络中同步,当服务器更新了 Health 并同步到客户端时，客户端会自动调用指定的函数 OnRep_Health。
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;//GAS 提供的一个结构，用来存储属性值,支持 GAS 的属性修改、同步和通知机制
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	
	//当 Health 在客户端被网络更新时，这个函数会被调用。
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props) const;
};


