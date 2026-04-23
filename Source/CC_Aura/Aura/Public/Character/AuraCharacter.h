// cccc

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CC_AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	/*当一个 AController（比如玩家控制器或 AI 控制器）接管这个角色时会调用。
	 *确保角色在被控制时，能力系统组件（ASC）和属性集（AttributeSet）正确初始化。
	 * PossessedBy → 服务器初始化。
	 */
	virtual void PossessedBy(AController* NewController) override;
	/*在网络同步时，当 PlayerState 在客户端更新时会调用。
	 *保证客户端也能正确拿到能力系统组件和属性集。
	 *因为 GAS 强依赖 PlayerState（它是网络可复制的），所以必须在客户端同步时重新初始化。
	 *  客户端初始化。
	 */
	virtual void OnRep_PlayerState() override;

	virtual int32 GetPlayerLevel() override;

private:
	virtual void InitAbilityActorInfo() override; 
};
