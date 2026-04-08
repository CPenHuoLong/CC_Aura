// cccc


#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	LastActor=ThisActor;
	ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());

	//射线检测的几种情况
	//1.最后一帧actor和当前帧actor都为空： 无响应
	//2.最后一帧actor为空，当前帧actor不为空： 高亮当前帧actor
	//3.最后一帧actor不为空，当前帧actor为空： 取消高亮最后一帧actor
	//4.俩个actor都不为空，但是最后一帧actor不是当前帧actor： 取消高亮最后一帧actor，高亮当前帧actor
	//5.俩个actor都不为空并且俩个actor相同： 无响应

	if (LastActor==nullptr && ThisActor!=nullptr)
	{
		ThisActor->HighLightActor();
	}
	if (LastActor!=nullptr && ThisActor==nullptr)
	{
		LastActor->UnHighLightActor();
	}
	
	if (LastActor!=nullptr && ThisActor!=nullptr && LastActor!=ThisActor)
	{
		LastActor->UnHighLightActor();
		ThisActor->HighLightActor();
	}
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);//检查是否在蓝图设置输入指针

	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);

	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move); 
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotaion(0.f,Rotation.Yaw,0.f);
	
	const FVector ForwardDirection=FRotationMatrix(YawRotaion).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotaion).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn=GetPawn<APawn>())
	//if (APawn* Pawn1=Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}
