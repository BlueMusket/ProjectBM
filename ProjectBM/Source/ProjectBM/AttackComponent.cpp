// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "BaseCharacter.h"
#include "BaseProjectile.h"
#include "BaseAnimInstance.h"
#include "BasePlayerController.h"
#include "BaseProjectileMovementComponent.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackComponent::HandlePowerTickEvent(float DeltaTime)
{
	float IncreaseRate = ThrowParam.PowerIncreaseRate;
	float NewValue = ThrowParam.ThrowPower + ( DeltaTime * IncreaseRate);

	if (ThrowParam.MaxPower < NewValue)
	{
		NewValue = 0.f;
	}

	ThrowParam.ThrowPower = NewValue;

	UE_LOG(LogTemp, Log, TEXT("Power : %f"), NewValue);
}

void UAttackComponent::HandleAngleTickEvent()
{
}


void UAttackComponent::OnThrow()
{
	SpawnProjectile();

}

void UAttackComponent::SpawnProjectile()
{
	if (nullptr == BP_PlayerProjectile)
	{
		return;
	}

	if (false == ThrowParam.IsValid)
	{
		return;
	}

	UWorld* World = GetWorld();

	if (nullptr == World)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	ABaseProjectile* NewProjectile = World->SpawnActor<ABaseProjectile>(BP_PlayerProjectile, ThrowParam.SpawnLocation, ThrowParam.ThrowRotation, SpawnParams);
	
	if (NewProjectile)
	{
		// 투사체의 UProjectileMovementComponent 설정
		UBaseProjectileMovementComponent* ProjectileMovement = NewProjectile->FindComponentByClass<UBaseProjectileMovementComponent>();
		if (ProjectileMovement)
		{
			// 초기 속도 설정
			ProjectileMovement->InitialSpeed = ThrowParam.ThrowPower;
			ProjectileMovement->MaxSpeed = ThrowParam.ThrowPower;
			ProjectileMovement->Velocity = FVector(ProjectileMovement->InitialSpeed, 0.f, 0.f);

			ProjectileMovement->RefreshPhysicsLinearVelocity();
			ProjectileMovement->TrajectorySimulating(ThrowParam.SpawnLocation);
		}
	}

	//// 발사 방향을 시각화하기 위한 디버그 라인 그리기
	FVector LineEnd = ThrowParam.SpawnLocation + (ThrowParam.ThrowRotation.Vector() * 1000); // 라인의 길이를 조절하려면 이 값을 변경하세요.
	FColor LineColor = FColor::Red; // 라인의 색상
	float LineDuration = 5.0f; // 라인이 화면에 표시되는 시간(초)
	bool bPersistentLines = false; // 라인이 지속적으로 남을지 여부

	DrawDebugLine(
		GetWorld(),
		ThrowParam.SpawnLocation,
		LineEnd,
		LineColor,
		bPersistentLines,
		LineDuration,
		0,
		5.0f // 라인의 두께
	);

	DrawDebugSphere(GetWorld(), ThrowParam.SpawnLocation, 50.0f , 5, FColor::Red, false , 5.0f);

	ThrowParam.IsValid = false;
}
