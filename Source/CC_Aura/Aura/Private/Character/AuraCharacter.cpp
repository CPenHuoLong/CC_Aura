// cccc


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement=true; //让角色的朝向自动跟随移动方向。
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);//设置角色旋转的速度 决定角色转向的灵敏度。
	GetCharacterMovement()->bConstrainToPlane=true;//让角色的移动被限制在一个平面上
	GetCharacterMovement()->bSnapToPlaneAtStart=true;

	//角色的旋转由 移动方向 + CharacterMovement 来决定
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//确保 ASC 和属性集在所有端都正确绑定。
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//确保 ASC 和属性集在所有端都正确绑定。
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	//拿到当前角色的 PlayerState
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	if (AuraPlayerState)
	{
		/*调用 InitAbilityActorInfo(AuraPlayerState, this)，把 OwnerActor 设置为 PlayerState，AvatarActor 设置为角色本身。
		OwnerActor → 谁拥有能力系统（PlayerState，保证网络复制正确）。
		AvatarActor → 谁在场景里表现这些能力（角色本身）。*/
		AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
		//初始化 AbilitySystemComponent：
		AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet=AuraPlayerState->GetAttributeSet();
	}

	if (AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD=Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	
}
