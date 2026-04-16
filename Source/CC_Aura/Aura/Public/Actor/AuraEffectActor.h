// cccc

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

// 定义什么时候应用效果（进入、离开、不应用）。
UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	// 当发生 Overlap（进入碰撞范围）时应用效果（比如进入火焰区域就掉血）。
	ApplyOnOverlap,
	// 当结束 Overlap（离开碰撞范围）时应用效果（比如离开治疗圈时扣除一次费用）。
	ApplyOnEndOverlap,
	//不应用任何效果。
	DoNotApply
};

//定义什么时候移除效果（离开、不移除）。
UENUM(BlueprintType)
enum class EEffectRemovePolicy
{
	// 当结束 Overlap（离开碰撞范围）时移除效果（比如离开加速圈后速度恢复正常）。
	RemoveOnEndOverlap,
	// 不移除效果（效果持续存在）
	DoNotRemove
};

UCLASS()
class CC_AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//从一个效果源（AAuraEffectActor）创建并应用一个 GameplayEffect 到目标 Actor 自己的 AbilitySystemComponent 上。
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	//当另一个 Actor（通常是角色）进入碰撞范围时触发。
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	//当另一个 Actor 离开碰撞范围时触发。
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	//当效果被移除时是否销毁这个 Actor。
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	bool bDestroyOnEffectRemoval=false;
	
	//用来存储一个 瞬时效果 (Instant) 的 GameplayEffect 类
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	//用来存储一个 持续效果 (Has Duration) 的 GameplayEffect 类。
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	////用来存储一个 无限持续效果  的 GameplayEffect 类。
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectRemovePolicy InfiniteEffectRemovePolicy = EEffectRemovePolicy::RemoveOnEndOverlap;
	
	//记录“哪个效果应用在了哪个 ASC 上”，方便以后移除。
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	float ActorLevel = 1.f;
	
};
