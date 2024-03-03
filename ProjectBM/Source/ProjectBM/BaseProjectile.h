// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "BaseProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API ABaseProjectile : public ABaseActor
{
	GENERATED_BODY()

public:
	ABaseProjectile(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp
			 , AActor* OtherActor, UPrimitiveComponent* OtherComp
			 , FVector NormalImpulse, const FHitResult& Hit);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = ( AllowPrivateAccecc = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccecc = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

protected:
	UPROPERTY(EditAnywhere, Category = Damage )
	float Damage = 34.f;
};
