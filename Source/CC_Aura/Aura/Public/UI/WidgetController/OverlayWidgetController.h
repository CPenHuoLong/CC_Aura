// cccc

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
//UE 官方命名规范：委托类型名必须以 Signature 结尾
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class CC_AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()


public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	//BlueprintAssignable = 允许蓝图给这个委托绑定事件
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;


protected:
	void HealthChange(const FOnAttributeChangeData& Data) const;
	void MaxHealthChange(const FOnAttributeChangeData& Data) const;
	void ManaChange(const FOnAttributeChangeData& Data) const;
	void MaxManaChange(const FOnAttributeChangeData& Data) const;
};
