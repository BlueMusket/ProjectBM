// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "BaseCharacter.h"
#include "BaseProjectile.h"
#include "BaseAnimInstance.h"

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

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	const FVector SpawnLocation = GetOwner<ABaseCharacter>()->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
	const FRotator Rotation = GetOwner()->GetActorForwardVector().Rotation();

	ABaseProjectile* NewProjectile = World->SpawnActor<ABaseProjectile>(BP_PlayerProjectile, SpawnLocation, Rotation, SpawnParams);
}
