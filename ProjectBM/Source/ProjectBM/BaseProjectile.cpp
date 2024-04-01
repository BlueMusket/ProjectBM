// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "BaseProjectileMovementComponent.h"
#include "PC.h"
#include "EffectActor.h"
#include "HealthComponent.h"

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

	// Static Mesh 컴포넌트 생성 및 초기화

	// 이 StaticMeshComponent를 액터의 루트 컴포넌트로 설정

	// 피직스 시뮬
	//SphereComponent->SetSimulatePhysics(true);
	
	// 피직스 시뮬은 Hit이벤트를 발생시킨다.
	//SphereComponent->SetNotifyRigidBodyCollision(true);

	// 충돌체를 Root로 둔다.
	
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