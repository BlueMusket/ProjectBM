// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "BaseCharacter.h"
#include "BaseProjectile.h"
#include "BaseAnimInstance.h"
#include "BasePlayerController.h"
#include "BaseProjectileMovementComponent.h"
#include "PC.h"

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

void UAttackComponent::SerializeThrowParam(FThrowParam& Param)
{
	Param.ThrowPower = ThrowPower;
	Param.ThrowRotation = ThrowRotation;
}

void UAttackComponent::DeserializeThrowParam(const FThrowParam& Param)
{
	SetThrowPower(Param.ThrowPower);
	SetThrowRotation(Param.ThrowRotation);
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

	UWorld* World = GetWorld();

	if (nullptr == World)
	{
		return;
	}

	APC* PC = GetOwner<APC>();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PC;

	FVector SpawnLocation = PC->GetThrowLocation();
	ABaseProjectile* NewProjectile = World->SpawnActor<ABaseProjectile>(BP_PlayerProjectile, SpawnLocation, ThrowRotation, SpawnParams);
	
	if (NewProjectile)
	{
		// 투사체의 UProjectileMovementComponent 설정
		UBaseProjectileMovementComponent* ProjectileMovement = NewProjectile->FindComponentByClass<UBaseProjectileMovementComponent>();
		if (ProjectileMovement)
		{
			// 초기 속도 설정
			//ProjectileMovement->InitialSpeed = ThrowPower;
			//ProjectileMovement->MaxSpeed = ThrowPower;
			ProjectileMovement->Velocity = FVector(ThrowPower, 0.f, 0.f);

			ProjectileMovement->RefreshPhysicsLinearVelocity();
			ProjectileMovement->TrajectorySimulating(SpawnLocation);
		}
	}
}
