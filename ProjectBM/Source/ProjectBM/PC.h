// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "PC.generated.h"


/**
 *
 */

class UInputContextComponent;
class ABasePlayerController;

UCLASS()
class PROJECTBM_API APC : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APC();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void ThrowNextStep(); // 던지기 스텝을 넘긴다.
	void ThrowRelease();
	void SpawnProjectile();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = Input)
	class UInputContextComponent* InputContext;

	UPROPERTY(EditAnywhere, Category = Projectile)
	class TSubclassOf<class ABaseProjectile> BP_PlayerProjectile;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	ABasePlayerController* PCController;


public:
	virtual void OnDeath_Implementation() override final;
	virtual void OnTakeDamage_Implementation() override final;
};
