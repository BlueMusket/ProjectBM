// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowParam.h"
#include "AttackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBM_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

public:
	void OnThrow();

	void SpawnProjectile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FThrowParam& GetThrowParam() { return ThrowParam; }
	void SetThrowParam(FThrowParam& Param) { ThrowParam = Param; }

public:
	UFUNCTION()
	void HandlePowerTickEvent(float DeltaTime);

	UFUNCTION()
	void HandleAngleTickEvent();

public:
	UPROPERTY(EditAnywhere, Category = Projectile)
	class TSubclassOf<class ABaseProjectile> BP_PlayerProjectile;

	UPROPERTY(EditAnywhere, Category = Projectile)
	FThrowParam ThrowParam;
};
