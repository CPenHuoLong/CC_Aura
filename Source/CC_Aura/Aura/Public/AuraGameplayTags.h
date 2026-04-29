// cccc

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * singleton containing native gameplay tags 一个全局唯一（Singleton）的对象，用来存放所有“原生（Native）Gameplay Tags”
 * UE 会把你在 C++ 中声明的所有 Gameplay Tags 放进一个全局单例里，这样整个游戏都能访问它们。
 */
//定义一个结构体作为“标签单例”
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() {return GameplayTags;}
	//游戏启动时注册标签。
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
 
protected:
 
private:
	static FAuraGameplayTags GameplayTags;
 
};


