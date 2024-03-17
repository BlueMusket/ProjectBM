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
class UAttackComponent;
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
	void UpdateThrowPower(float DeltaTime);
	FVector GetThrowLocation();

	void SetThrowPower(float Power);
	float GetThrowPower();
	void SetThrowRotation(FRotator Rotation);

	void VaryHealth(float Value);
public:

	void OnThrow();

	// 서버에 요청
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerOnThrow(FThrowParam Param);
	void ServerOnThrow_Implementation(FThrowParam Param);
	bool ServerOnThrow_Validate(FThrowParam Param);

	// 서버에서 멀티케스팅
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnThrow(FThrowParam Param);
	void MulticastOnThrow_Implementation(FThrowParam Param);

	UFUNCTION(Client, Reliable)
	void ClientOnThrow(FThrowParam Param);
	void ClientOnThrow_Implementation(FThrowParam Param);


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	class UInputContextComponent* InputContextComponent;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	ABasePlayerController* PCController;

public:
	virtual void OnDeath_Implementation() override final;
	virtual void OnTakeDamage_Implementation() override final;
};
