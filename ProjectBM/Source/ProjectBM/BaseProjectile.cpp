// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "BaseProjectileMovementComponent.h"
#include "PC.h"
#include "HealthComponent.h"

ABaseProjectile::ABaseProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PrimaryActorTick.bCanEverTick = true;
	// 
	// 충돌용 Component 생성
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

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
	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BaseProjectileComponent"));
	//ProjectileMovement->UpdatedComponent = SphereComponent;
	//ProjectileMovement->ProjectileGravityScale = 1.0f;
	//ProjectileMovement->InitialSpeed = 800.f;
	//ProjectileMovement->MaxSpeed = 800.f;
	//ProjectileMovement->bAutoActivate = true;  // 자동 활성화

	// 3초 후에 삭제
	InitialLifeSpan = 10.0f;
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	// 이벤트 바인드
	SphereComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
}


void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	//UE_LOG("");
}