// cccc


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency=100.f; //每秒向客户端发送更新的次数 最多更新 100 次

	/*父类里声明基类指针 UAbilitySystemComponent  是为了 通用性和兼容性。
	构造时用自己派生的类 UAuraAbilitySystemComponent 是为了 扩展功能。
	这是典型的 面向对象编程模式：对外暴露基类接口，内部用子类实现。*/
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//Mixed 对不同类型的客户端复制不同粒度的信息。平衡性能和功能。玩家自己能看到完整效果，而别人只看到简化版。
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState,Level);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
