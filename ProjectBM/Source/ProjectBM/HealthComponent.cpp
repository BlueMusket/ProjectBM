// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "BaseCharacterInterface.h" 
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	: Super()
	, Health(MaxHealth)
{
	// Tick 이벤트는 X
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::VaryHealth(float Value)
{
	float OldHealth = Health;
	float NewHealth = OldHealth + Value;


	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);

	if (0.f == Health && true == GetOwner()->Implements<UBaseCharacterInterface>())
	{
		IBaseCharacterInterface::Execute_OnDeath(GetOwner());
	}

	// Owner Actor 처리
}