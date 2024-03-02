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

	UWorld* World = GetWorld();

	if (nullptr == World)
	{
		return;
	}

	ABasePlayerController* Controller = GetOwner<ABaseCharacter>()->GetController<ABasePlayerController>();

	// 마우스 위치를 저장할 변수
	float MouseX, MouseY;
	FVector CursorLocation, CursorDirection;
	FVector OutLocation;
	if (Controller->GetMousePosition(MouseX, MouseY))
	{
		if (Controller->DeprojectScreenPositionToWorld(MouseX, MouseY, CursorLocation, CursorDirection))
		{
			// 카메라 위치에서 마우스가 가리키는 방향으로 레이를 쏴서 X = PlaneX 평면과의 교차점을 찾습니다.
			// 레이의 방정식: P = WorldLocation + t * WorldDirection
			// 교차점에서 X = PlaneX 이므로, t = (PlaneX - WorldLocation.X) / WorldDirection.X
			if (FMath::Abs(CursorDirection.X) > KINDA_SMALL_NUMBER) // 0으로 나누는 것을 방지
			{
				float t = (0 - CursorLocation.X) / CursorDirection.X;
				OutLocation = CursorLocation + t * CursorDirection;

				// OutLocation은 이제 X = 0 평면에서 마우스 위치에 해당하는 월드 좌표입니다.
			}
		}
	}

	// 마우스 위치를 월드 위치와 방향으로 변환
	//Controller->DeprojectMousePositionToWorld(CursorLocation, CursorDirection);
	CursorLocation.X = 0.f;
	FVector SpawnLocation = GetOwner<ABaseCharacter>()->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
	SpawnLocation.X = 0.f;
	// 발사 방향 계산
	FVector Direction = (OutLocation - SpawnLocation).GetSafeNormal();
	FRotator FireRotation = Direction.Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	ABaseProjectile* NewProjectile = World->SpawnActor<ABaseProjectile>(BP_PlayerProjectile, SpawnLocation, FireRotation, SpawnParams);
	
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

	// 발사 방향을 시각화하기 위한 디버그 라인 그리기
	FVector LineEnd = SpawnLocation + (Direction * 1000); // 라인의 길이를 조절하려면 이 값을 변경하세요.
	FColor LineColor = FColor::Red; // 라인의 색상
	float LineDuration = 5.0f; // 라인이 화면에 표시되는 시간(초)
	bool bPersistentLines = false; // 라인이 지속적으로 남을지 여부

	DrawDebugLine(
		GetWorld(),
		SpawnLocation,
		LineEnd,
		LineColor,
		bPersistentLines,
		LineDuration,
		0,
		5.0f // 라인의 두께
	);

	DrawDebugSphere(GetWorld(), OutLocation, 50.0f , 5, LineColor, false , 5.0f);
}
