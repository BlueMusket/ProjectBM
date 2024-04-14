// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "BaseProjectile.generated.h"

class  AEffectActor;
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

	virtual void PostActorCreated() override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp
			 , AActor* OtherActor, UPrimitiveComponent* OtherComp
			 , FVector NormalImpulse, const FHitResult& Hit);

public:

	UPROPERTY(EditAnywhere)
	class TSubclassOf<class AEffectActor> BP_EffectActor;

	UPROPERTY(VisibleAnywhere, meta = ( AllowPrivateAccecc = "true"))
	class USphereComponent* SphereComponent;

	// Static Mesh 컴포넌트를 저장하는 포인터
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccecc = "true"))
	class UBaseProjectileMovementComponent* ProjectileMovement;

private:
	void InitVelocity();

protected:
	UPROPERTY(EditAnywhere, Category = Damage )
	float Damage = 34.f;
};
