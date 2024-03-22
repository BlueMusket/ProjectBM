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
#include "InputContextComponent.h"
#include "AttackComponent.h"
#include "BaseAnimInstance.h"


APC::APC()
	: Super()
	, PCController(nullptr)
{
	InputContextComponent = CreateDefaultSubobject<UInputContextComponent>(TEXT("InputContext"));
	
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

void APC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (IsValid(PCController))
	//{
	//	CEntryInfo* EntryInfo = PCController->GetEntryInfo();
	//	const FString SessionIdStr = FString::Printf(TEXT("SessionId : %d"), EntryInfo->GetSessionId());

	//	DrawDebugString(GetWorld(), GetActorLocation(), SessionIdStr, nullptr, FColor::White, 0.0f, true);
	//}
}

void APC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (nullptr != InputContextComponent)
	{
		InputContextComponent->SetupPlayerInputComponent(PlayerInputComponent);
	}
}

FVector APC::GetThrowLocation()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
	SpawnLocation.X = 0.f; // 혹시 모를 X축 처리

	return SpawnLocation;
}

void APC::SetThrowPower(float Power)
{
	AttackComponent->SetThrowPower(Power);
}

float APC::GetThrowPower()
{
	return AttackComponent->GetThrowPower();
}

void APC::SetThrowRotation(FRotator Rotation)
{
	AttackComponent->SetThrowRotation(Rotation);
}

void APC::VaryHealth(float Value)
{
	HealthComponent->VaryHealth(Value);
}

void APC::OnThrow()
{
	FThrowParam Param;

	AttackComponent->SerializeThrowParam(Param);

	MulticastOnThrow_Implementation(Param);
	//if (HasAuthority())
	//{
	//	ServerOnThrow_Implementation(Param);
	//}
	//else
	//{
	//	ServerOnThrow(Param);
	//}
}

void APC::ServerOnThrow_Implementation(FThrowParam Param)
{
	// 검증 검증


	// 해당 클라이언트만 처리
	ClientOnThrow(Param);

	// 멀티 케스팅 처리
	MulticastOnThrow(Param);
}

bool APC::ServerOnThrow_Validate(FThrowParam Param)
{
	return true;
}


void APC::MulticastOnThrow_Implementation(FThrowParam Param)
{
	// 서버값을 사용한다.
	AttackComponent->DeserializeThrowParam(Param);

	UBaseAnimInstance* AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr != AnimInstance)
	{
		AnimInstance->PlayThrow();
	}
}

void APC::ClientOnThrow_Implementation(FThrowParam Param)
{
	// 검증 검증

	//SpawnProjectile();
}


// 인터페이스 호출용
void APC::OnDeath_Implementation()
{
	//PCController->ShowRestartWidget();

	//UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

// 인터페이스 호출용
void APC::OnTakeDamage_Implementation()
{
	PCController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
	//UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}