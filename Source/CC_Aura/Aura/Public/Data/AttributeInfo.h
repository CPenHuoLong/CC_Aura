// cccc

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"


USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	//属性标签,用 GameplayTag 来标识属性,这是属性的“唯一 ID”
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	//属性名称 用于 UI 显示的名字 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	//属性描述 属性的说明文字
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	//属性数值 这个值通常由角色属性系统（AttributeSet）更新 在 UI 中显示
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
	
};

/**
 * 
 */
UCLASS()
class CC_AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//UI想显示属性时，通过Tag查找对应的名字、描述、图标等. 角色属性变化时，用 Tag 找到对应的 UI 信息
	FAuraAttributeInfo FindAttributeInForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false ) const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
};
