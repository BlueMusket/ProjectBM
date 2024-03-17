// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectActor.h"
#include "PC.h"

// Sets default values
AEffectActor::AEffectActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, IntervalTick(0.f)
	, bIsActive(false)
	, LastTick(0.f)
	, NextActionTick(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	// Initialize the static mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEffectActor::Initialize(FVector CollisionSize, float LifeSpan)
{
	CollisionComponent->SetBoxExtent(CollisionSize);
	SetLifeSpan(LifeSpan);
}

bool AEffectActor::IsActive()
{
	return bIsActive;
}

void AEffectActor::Deactive()
{
	bIsActive = false;
}

void AEffectActor::FindTargets(TArray<AActor*>& OutTargets)
{
	CollisionComponent->GetOverlappingActors(OutTargets);
}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 아직 다른 조건이 없으니 true
	bIsActive = true;
}

// Called every frame
void AEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (false == IsActive())
	{
		return;
	}

	LastTick += DeltaTime * 1000.0f; // second를 miliSecond로 변환
	
	if (LastTick < NextActionTick)
	{
		return;
	}

	// 동작 시작
	// 지금은 1회만

	{
		TArray<AActor*> Targets;
		FindTargets(Targets); // 나중에 TargetType등이 추가되어야함

		for (AActor* Actor : Targets)
		{
			APC* PC = Cast<APC>(Actor);
			if (NULL != PC)
			{
				PC->VaryHealth(-50);
			}
			//EffectHandle->Execute(Target);
		}
		
		Deactive();
	}


	NextActionTick = LastTick + IntervalTick;
}
