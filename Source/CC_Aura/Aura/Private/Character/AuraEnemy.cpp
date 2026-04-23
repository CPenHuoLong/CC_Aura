// cccc


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/CC_Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	/*父类里声明基类指针 UAbilitySystemComponent  是为了 通用性和兼容性。
	构造时用自己派生的类 UAuraAbilitySystemComponent 是为了 扩展功能。
	这是典型的 面向对象编程模式：对外暴露基类接口，内部用子类实现。*/
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//Minimal 只复制最少量的 Gameplay Effect 信息。适合大量 NPC 或不重要的对象，减少带宽消耗。
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
	
}

void AAuraEnemy::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
}

void AAuraEnemy::InitAbilityActorInfo()
{
	/*InOwnerActor
	逻辑上的“拥有者”Actor。通常是玩家控制器（PlayerController）或者角色类（Character）。用来标识谁真正拥有这个 AbilitySystemComponent。
	InAvatarActor
	表示“化身”Actor，也就是实际在场景里表现的对象。通常是 Pawn 或 Character。这个 Actor 是技能和效果真正作用的目标，比如角色的 Mesh、动画、属性。
	InitAbilityActorInfo 的作用就是 把能力系统组件和具体的游戏对象绑定起来，明确：
	谁拥有这个能力系统（OwnerActor） 在场景里表现这些能力（AvatarActor） 这是 GAS 初始化的关键步骤，没有这一步，技能和属性不会正确工作。*/
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
