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
	UFUNCTION()
	void SerializeThrowParam(FThrowParam& Param);
	void DeserializeThrowParam(const FThrowParam& Param);

	UFUNCTION()
	void OnThrow();

	void SpawnProjectile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void SetThrowPower(float NewThrowPower) { ThrowPower = NewThrowPower; }
	float GetThrowPower() { return ThrowPower; }

	void SetThrowRotation(FRotator NewRotation) { ThrowRotation = NewRotation; }
	FRotator GetThrowRotation() { return ThrowRotation; }

public:
	UPROPERTY(EditAnywhere, Category = Projectile)
	class TSubclassOf<class ABaseProjectile> BP_PlayerProjectile;

private:
	FRotator ThrowRotation;
	float ThrowPower;
};
