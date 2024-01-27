// Fill out your copyright notice in the Description page of Project Settings.


#include "PC.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "HealthComponent.h"
APC::APC()
	: Super()
	, PCController(nullptr)
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
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &APC::OnJump);
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

void APC::OnThrow(const FInputActionValue& Value)
{

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