// cccc


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
