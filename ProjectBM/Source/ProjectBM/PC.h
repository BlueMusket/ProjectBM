// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "PC.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EThrowState : uint8
{
	EThrowState_None  UMETA(DisplayName="None"),
	EThrowState_Angle UMETA(DisplayName="Angle"),
	EThrowState_AngleEnd UMETA(DisplayName="AngleEnd"),
	EThrowState_Power UMETA(DisplayName="Power"),
	EThrowState_Shoot UMETA(DisplayName="Shoot"),
	EThrowState_Count UMETA(DisplayName="Count"),
};

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
	UFUNCTION(BlueprintCallable)
	EThrowState GetThrowState();

	void ThrowNextStep(); // 던지기 스텝을 넘긴다.
	void ThrowRelease();
	void SpawnProjectile();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IC_PC;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Throw;

	UPROPERTY(EditAnywhere, Category = Projectile)
	class TSubclassOf<class ABaseProjectile> BP_PlayerProjectile;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnMove(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	void OnShootRelease(const FInputActionValue& Value);
	void OnThrow(const FInputActionValue& Value);


private:
	ABasePlayerController* PCController;
	EThrowState ThrowState;


public:
	virtual void OnDeath_Implementation() override final;
	virtual void OnTakeDamage_Implementation() override final;
};
