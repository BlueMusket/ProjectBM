// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "BaseCharacter.h"
#include "BaseProjectile.h"
#include "BaseAnimInstance.h"
#include "BasePlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAttackComponent::OnThrow()
{
	SpawnProjectile();

}

void UAttackComponent::SpawnProjectile()
{
	if (nullptr == BP_PlayerProjectile)
	{
		return;
	}

	if (false == ThrowParam.IsValid)
	{
		return;
	}

	UWorld* World = GetWorld();

	if (nullptr == World)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	ABaseProjectile* NewProjectile = World->SpawnActor<ABaseProjectile>(BP_PlayerProjectile, ThrowParam.SpawnLocation, ThrowParam.ThrowRotation, SpawnParams);
	
	if (NewProjectile)
	{
		// 투사체의 UProjectileMovementComponent 설정
		UProjectileMovementComponent* ProjectileMovement = NewProjectile->FindComponentByClass<UProjectileMovementComponent>();
		if (ProjectileMovement)
		{
			//ProjectileMovement->InitialSpeed = 8000.f;
			//ProjectileMovement->MaxSpeed = 8000.f;
			//ProjectileMovement->Velocity = Direction * 8000.f; // 방향과 파워를 곱하여 최종 속도 설정
		}
	}

	//// 발사 방향을 시각화하기 위한 디버그 라인 그리기
	//FVector LineEnd = ThrowParam.SpawnLocation + (Direction * 1000); // 라인의 길이를 조절하려면 이 값을 변경하세요.
	//FColor LineColor = FColor::Red; // 라인의 색상
	//float LineDuration = 5.0f; // 라인이 화면에 표시되는 시간(초)
	//bool bPersistentLines = false; // 라인이 지속적으로 남을지 여부

	//DrawDebugLine(
	//	GetWorld(),
	//	ThrowParam.SpawnLocation,
	//	LineEnd,
	//	LineColor,
	//	bPersistentLines,
	//	LineDuration,
	//	0,
	//	5.0f // 라인의 두께
	//);

	DrawDebugSphere(GetWorld(), ThrowParam.SpawnLocation, 50.0f , 5, FColor::Red, false , 5.0f);

	ThrowParam.IsValid = false;
}
