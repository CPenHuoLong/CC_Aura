// cccc


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}


void AAuraPlayerController::AutoRun()
{
	
	if(!bAutoRunning) return;//如果 bAutoRunning == false，说明没有处于自动跑动状态，直接返回。
	if (APawn* ControllerPawn = GetPawn())
	{
		//找到角色当前位置在 Spline 曲线上的最近点 保证角色沿着预先生成的路径（Spline）移动
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		//根据最近点，获取Spline的方向向量 
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		//把这个方向作为输入传给 Pawn → 角色就会沿着曲线移动。
		ControllerPawn->AddMovementInput(Direction);
		//计算角色在 Spline 上的当前位置与目标点（CachedDestination）的距离。
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius) //如果距离小于接受半径 AutoRunAcceptanceRadius，说明已经到达目的地。
		{
			bAutoRunning = false; //设置 bAutoRunning = false → 停止自动跑动。
		}
	}
}


void AAuraPlayerController::CursorTrace()
{
	
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

	if (LastActor != ThisActor)
	{
		if(LastActor) LastActor->UnHighLightActor();
		if(ThisActor) ThisActor->HighLightActor();
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//如果输入的 Tag 不是鼠标左键 (LMB)，就直接调用 AbilitySystem 的 AbilityInputTagHeld，然后返回。
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		
		return;
	}
	//如果正在目标锁定模式（比如选中敌人），那么 LMB 长按也交给 AbilitySystem。
	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	
	}
	else
	{
		const APawn* ControllerPawn =GetPawn();
		if (FollowTime <= ShortPressThreshold && ControllerPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControllerPawn->GetActorLocation(),CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const auto& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
				}
				//把路径的 终点坐标 存到 CachedDestination
				if (NavPath->PathPoints.Num() > 0)
				{
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				}
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
	
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//如果输入的 Tag 不是鼠标左键 (LMB)，就直接调用 AbilitySystem 的 AbilityInputTagHeld，然后返回。
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	
		return;
	}
	//如果正在目标锁定模式（比如选中敌人），那么 LMB 长按也交给 AbilitySystem。
	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		
	}
	else
	{
		//累加跟随时间，用来区分短按和长按。
		FollowTime += GetWorld()->GetDeltaSeconds();
		//用鼠标射线检测，获取点击位置。
		
		if (CursorHit.bBlockingHit)  CachedDestination = CursorHit.ImpactPoint;
	
		//计算方向并移动 Pawn
		if (APawn* ControllerPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
	
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);//检查是否在蓝图设置输入指针

	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}

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

	UAuraInputComponent* AuraInputComponent=CastChecked<UAuraInputComponent>(InputComponent);

	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
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
