// cccc

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	//UE 的反射系统（蓝图、序列化）要求结构体必须能默认构造 如果你只写有参构造，编译器不会自动生成默认构造 → 蓝图会报错
	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS):
	PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS) {};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController=nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState=nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent=nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet=nullptr;
	
};


/**
 * 
 */
UCLASS()
class CC_AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	virtual void BindCallbacksToDependencies();

	virtual void BroadcastInitialValues();
protected:
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
