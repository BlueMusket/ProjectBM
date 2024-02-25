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

	void OnThrow();

	// 서버에 요청
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerOnThrow();
	void ServerOnThrow_Implementation();
	bool ServerOnThrow_Validate();

	// 서버에서 멀티케스팅
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnThrow();
	void MulticastOnThrow_Implementation();

	UFUNCTION(Client, Reliable)
	void ClientOnThrow();
	void ClientOnThrow_Implementation();


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
