// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PC.h"
#include "HealthComponent.h"

ABaseProjectile::ABaseProjectile()
	: Super()
{
	// 충돌용 Component 생성
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetSphereRadius(35.f);

	// 
	SphereComponent->SetCollisionProfileName(FName("BaseProjectile"));

	// 피직스 시뮬
	SphereComponent->SetSimulatePhysics(true);
	
	// 피직스 시뮬은 Hit이벤트를 발생시킨다.
	SphereComponent->SetNotifyRigidBodyCollision(true);

	// 충돌체를 Root로 둔다.
	RootComponent = SphereComponent;

	// Movement 시작
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1500.f;

}

void ABaseProjectile::BeginPlay()
{
	// 이벤트 바인드
	SphereComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp
						  , AActor* OtherActor, UPrimitiveComponent* OtherComp
						  , FVector NormalImpulse, const FHitResult& Hit)
{
	APC* PC = Cast<APC>(OtherActor);
	if ( NULL != PC)
	{
		UHealthComponent* HealthComponent = PC->FindComponentByClass<UHealthComponent>();

		if (NULL != HealthComponent)
		{
			HealthComponent->VaryHealth(-Damage);
		}
		Destroy();
	}
}