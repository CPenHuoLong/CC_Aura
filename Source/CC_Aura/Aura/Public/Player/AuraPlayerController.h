// cccc

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class CC_AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();//鼠标射线检测

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	FHitResult CursorHit;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	//缓存目标目的地坐标 角色自动跑动时，保存要到达的点
	FVector CachedDestination = FVector::ZeroVector;
	//用于判断按键持续时间
	float FollowTime = 0.f;
	//区分“短按”和“长按”，比如短按触发一次技能，长按进入自动跑动。
	float ShortPressThreshold = 0.5f;
	//逻辑开关，控制角色是否正在沿着路径自动移动。
	bool bAutoRunning = false;
	bool bTargeting = false;
	//当角色距离目标点小于这个半径时，认为到达目的地，停止自动跑动。
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	//存储自动跑动的路径（曲线），角色沿着 Spline 移动。
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	//自动跑动逻辑
	void AutoRun();
};
