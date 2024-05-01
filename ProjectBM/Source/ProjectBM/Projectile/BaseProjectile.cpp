// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "../Component/BaseProjectileMovementComponent.h"
#include "../Character/PC.h"
#include "../Effect/EffectActor.h"
#include "../Component/AttackComponent.h"
#include "../Component/HealthComponent.h"
#include "Components/SphereComponent.h"

//#if UE_EDITOR
//PRAGMA_DISABLE_OPTIMIZATION
//#endif

ABaseProjectile::ABaseProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	// 
	SphereStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	SphereStaticMeshComponent->SetCollisionProfileName(FName("BaseProjectile"));

	// 충돌용 Component 생성
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName(FName("BaseProjectile"));
	SphereComponent->SetSphereRadius(35.f);
	RootComponent = SphereComponent;

	SphereStaticMeshComponent->SetupAttachment(SphereComponent);

	// Movement 시작
	ProjectileMovement = CreateDefaultSubobject<UBaseProjectileMovementComponent>(TEXT("BaseProjectileMovementComponent"));
	ProjectileMovement->UpdatedComponent = SphereComponent;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
	ProjectileMovement->bAutoActivate = true;  // 자동 활성화
	ProjectileMovement->InitialSpeed = 0.f;
	ProjectileMovement->MaxSpeed = 0.f;

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

void ABaseProjectile::PostActorCreated()
{
	InitVelocity();
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp
						  , AActor* OtherActor, UPrimitiveComponent* OtherComp
						  , FVector NormalImpulse, const FHitResult& Hit)
{
	UWorld* World = GetWorld();

	if (nullptr == World)
	{
		return;
	}

	APC* PC = GetOwner<APC>();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PC;
	FVector SpawnLocation = GetActorLocation();
	AEffectActor* NewEffect = World->SpawnActor<AEffectActor>(BP_EffectActor, SpawnLocation, FRotator(), SpawnParams);

	if (nullptr != NewEffect)
	{
		NewEffect->Initialize(FVector(100, 100, 100), 1000);
	}

	Destroy();
}

void ABaseProjectile::InitVelocity()
{
	APC* PC = GetOwner<APC>();

	if (nullptr == PC)
	{
		return;
	}

	UAttackComponent* AttackComponent = PC->GetComponentByClass<UAttackComponent>();

	if (nullptr != AttackComponent)
	{
		float Power = AttackComponent->GetThrowPower();

		ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * Power;
	}
}
