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
	: MaxThrowPower(1000.f)
	, ThrowPowerIncreaseRate(100.f)
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

	if (true == bIsOnPower)
	{
		TickThrowPower(DeltaTime);
	}

	/*if (true == bIsOnPower)
	{
		OnPowerTickEvent.Broadcast(DeltaTime);
	}*/
	// ...
}

void UInputContextComponent::TickThrowPower(float DeltaTime)
{
	APC* PC = GetOwner<APC>();

	float OldThrowPower = PC->GetThrowPower();

	float NewValue = OldThrowPower + (DeltaTime * ThrowPowerIncreaseRate);

	if (MaxThrowPower < NewValue)
	{
		NewValue = 0.f;
	}

	PC->SetThrowPower(NewValue);

}


void UInputContextComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (NULL != EnhancedInputComponent)
	{
		APC* PC = GetOwner<APC>();
		ABasePlayerController* Controller = PC->GetController<ABasePlayerController>();

		UEnhancedInputLocalPlayerSubsystem* EnhancedSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Controller->GetLocalPlayer());

		if (NULL != EnhancedSubSystem)
		{
			// 컨텍스트 객체 전달, 우선순위 1
			EnhancedSubSystem->AddMappingContext(IC_PC, 1);
		}

		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UInputContextComponent::OnMove);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &UInputContextComponent::OnJump);
		EnhancedInputComponent->BindAction(IA_Angle, ETriggerEvent::Triggered, this, &UInputContextComponent::OnAngle);

		EnhancedInputComponent->BindAction(IA_Power, ETriggerEvent::Started, this, &UInputContextComponent::OnPrePower);
		EnhancedInputComponent->BindAction(IA_Power, ETriggerEvent::Completed, this, &UInputContextComponent::OnPostPower);
	}
}

void UInputContextComponent::OnMove(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	{
		APC* PC = GetOwner<APC>();
		ABasePlayerController* Controller = PC->GetController<ABasePlayerController>();

		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		PC->AddMovementInput(Direction, InputValue.Y);
	}
}

void UInputContextComponent::OnJump(const FInputActionValue& Value)
{
	APC* PC = GetOwner<APC>();

	PC->Jump();
}

void UInputContextComponent::OnAngle(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	APC* PC = GetOwner<APC>();
	ABasePlayerController* Controller = PC->GetController<ABasePlayerController>();

	FVector ThrowLocation = PC->GetThrowLocation();
	FVector MouseLocation = Controller->OnScreenLocationFromMouse();

	// 발사 방향 계산
	FVector Direction = (MouseLocation - ThrowLocation).GetSafeNormal();
	FRotator ThrowRotation = Direction.Rotation();

	MouseLocation.X = 0.f;

	FVector Target = MouseLocation + (ThrowRotation.Vector() * 100.f);

	// DrawDebugLine(GetWorld(), MouseLocation, Target, FColor::Red, false , 10);
	//DrawDebugSphere(GetWorld(), MouseLocation, 10.0f, 5, FColor::Red, false, 5.0f);
	
	PC->SetThrowRotation(ThrowRotation);
}

void UInputContextComponent::OnPrePower(const FInputActionValue& Value)
{
	bIsOnPower = true;
}

void UInputContextComponent::OnPostPower(const FInputActionValue& Value)
{
	bIsOnPower = false;

	APC* PC = GetOwner<APC>();
	PC->OnThrow();
}

