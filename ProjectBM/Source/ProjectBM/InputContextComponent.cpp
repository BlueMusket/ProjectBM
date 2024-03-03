// Fill out your copyright notice in the Description page of Project Settings.


#include "InputContextComponent.h"
#include "Components/InputComponent.h"

#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "PC.h"
#include "AttackComponent.h"

// Sets default values for this component's properties
UInputContextComponent::UInputContextComponent()
	: bIsOnPower(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputContextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInputContextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 공격 틱 처리
	if (true == bIsOnPower)
	{
		OnPowerTickEvent.Broadcast(DeltaTime);
	}
	// ...
}

void UInputContextComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (NULL != EnhancedInputComponent)
	{
		APC* OwnerCharacter = Cast<APC>(GetOwner());
		ABasePlayerController* Controller = OwnerCharacter->GetController<ABasePlayerController>();

		UEnhancedInputLocalPlayerSubsystem* EnhancedSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Controller->GetLocalPlayer());

		if (NULL != EnhancedSubSystem)
		{
			// 컨텍스트 객체 전달, 우선순위 1
			EnhancedSubSystem->AddMappingContext(IC_PC, 1);
		}

		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UInputContextComponent::OnMove);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &UInputContextComponent::OnJump); // 임시, 슈팅 종료 이벤트로 들어와야한다.
		EnhancedInputComponent->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &UInputContextComponent::OnThrow);
		EnhancedInputComponent->BindAction(IA_Angle, ETriggerEvent::Triggered, this, &UInputContextComponent::OnAngle);

		EnhancedInputComponent->BindAction(IA_Power, ETriggerEvent::Started, this, &UInputContextComponent::OnPrePower);
		//EnhancedInputComponent->BindAction(IA_Power, ETriggerEvent::Triggered, this, &UInputContextComponent::OnPower);
		EnhancedInputComponent->BindAction(IA_Power, ETriggerEvent::Completed, this, &UInputContextComponent::OnPostPower);
	}
}

void UInputContextComponent::OnMove(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	{
		APC* OwnerCharacter = Cast<APC>(GetOwner());
		ABasePlayerController* Controller = OwnerCharacter->GetController<ABasePlayerController>();

		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		OwnerCharacter->AddMovementInput(Direction, InputValue.Y);
	}
}

void UInputContextComponent::OnJump(const FInputActionValue& Value)
{
	APC* OwnerCharacter = Cast<APC>(GetOwner());

	OwnerCharacter->Jump();
}

void UInputContextComponent::OnThrow(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	APC* OwnerCharacter = Cast<APC>(GetOwner());
	OwnerCharacter->OnThrow();
}


void UInputContextComponent::OnAngle(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	APC* OwnerCharacter = Cast<APC>(GetOwner());
	ABasePlayerController* Controller = OwnerCharacter->GetController<ABasePlayerController>();

	float MouseX, MouseY;
	if (Controller->GetMousePosition(MouseX, MouseY))
	{
		Controller->SetThrowMousePos(MouseX, MouseY);
	}

	// 나중에 UI 처리?
	//OnAngleTickEvent.Broadcast();
}

void UInputContextComponent::OnPrePower(const FInputActionValue& Value)
{
	// 사전 동작 필요하면 작업
	// 
	//UE_LOG(LogTemp, Log, TEXT("Powerrr"));
	//FVector2D InputValue = Value.Get<FVector2D>();

	//APC* OwnerCharacter = Cast<APC>(GetOwner());
	//ABasePlayerController* Controller = OwnerCharacter->GetController<ABasePlayerController>();

	//if (nullptr != Controller)
	//{
	//	Controller->UpdateAttackPower();
	//}

	bIsOnPower = true;
}

void UInputContextComponent::OnPower(const FInputActionValue& Value)
{
}

void UInputContextComponent::OnPostPower(const FInputActionValue& Value)
{

	APC* OwnerCharacter = Cast<APC>(GetOwner());
	OwnerCharacter->OnThrow();

	bIsOnPower = false;
}

