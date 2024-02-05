// Fill out your copyright notice in the Description page of Project Settings.


#include "PC.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BasePlayerController.h"
#include "BaseProjectile.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "HealthComponent.h"

APC::APC()
	: Super()
	, PCController(nullptr)
	, ThrowState(EThrowState::EThrowState_None)
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 800.f;
	CameraArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	CameraArm->bUsePawnControlRotation = false;

	// 컨트롤러가 회전할 때 캐릭터는 회전하지 않도록 설정한다.
	// 캐릭터가 카메라에 영향을 주도록 놔둔다.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터 무브먼트를 설정한다.
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APC::BeginPlay()
{
	Super::BeginPlay();

	PCController->UpdateHealthPercent(HealthComponent->GetHealthPercent());

#if UE_SERVER

#endif
}

EThrowState APC::GetThrowState()
{
	return ThrowState;
}

void APC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (NULL != EnhancedInputComponent)
	{
		PCController = Cast< ABasePlayerController>(Controller);
		UEnhancedInputLocalPlayerSubsystem* EnhancedSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PCController->GetLocalPlayer());

		if (NULL != EnhancedSubSystem)
		{
			// 컨텍스트 객체 전달, 우선순위 1
			EnhancedSubSystem->AddMappingContext(IC_PC, 1);
		}

		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APC::OnMove);
		//EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &APC::OnJump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &APC::OnShootRelease); // 임시, 슈팅 종료 이벤트로 들어와야한다.
		EnhancedInputComponent->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &APC::OnThrow);
	}

}

void APC::OnMove(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();
	// FLT_EPSILON < FMath::Abs(value)
	if (NULL != Controller/* && 0.f != value*/)
	{
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, InputValue.Y);
	}
}

void APC::OnJump(const FInputActionValue& Value)
{
	Jump();
}

void APC::OnShootRelease(const FInputActionValue& Value)
{
	ThrowState = EThrowState::EThrowState_None;
}

void APC::OnThrow(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (1 == InputValue.X) // 누르는중
	{
		ThrowNextStep();
	}
	else if (0 == InputValue.X) // 키땜
	{
		ThrowRelease();
	}
}

void APC::SpawnProjectile()
{
	if (nullptr == BP_PlayerProjectile)
	{
		return;
	}

	UWorld* World = GetWorld();

	if (nullptr == World)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	const FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
	const FRotator Rotation = GetActorForwardVector().Rotation();

	ABaseProjectile* NewProjectile = World->SpawnActor<ABaseProjectile>(BP_PlayerProjectile, SpawnLocation, Rotation, SpawnParams);
}

void APC::ThrowNextStep()
{
	switch (ThrowState)
	{
		case EThrowState::EThrowState_None: // 각도 조절 시작
		{
			ThrowState = EThrowState::EThrowState_Angle;
		}
		break;
		
		case EThrowState::EThrowState_AngleEnd:
		{
			ThrowState = EThrowState::EThrowState_Power;
		}
		break;
	}
}

void APC::ThrowRelease()
{
	switch (ThrowState)
	{
		case EThrowState::EThrowState_Angle:
		{
			// 뭔가 이벤트 처리?
			ThrowState = EThrowState::EThrowState_AngleEnd;
		}
		break;

		case EThrowState::EThrowState_Power:
		{
			// 바로 슈팅
			ThrowState = EThrowState::EThrowState_Shoot;
		}
		break;
	}
}

// 인터페이스 호출용
void APC::OnDeath_Implementation()
{
	PCController->ShowRestartWidget();

	//UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

// 인터페이스 호출용
void APC::OnTakeDamage_Implementation()
{
	PCController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
	//UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}