// cccc

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CC_AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintCallable)//蓝图调用
	void SetWidgetController(UObject* InWidgetController);

protected:
	UFUNCTION(BlueprintImplementableEvent)//蓝图编写
	void WidgetControllerSet();
};
