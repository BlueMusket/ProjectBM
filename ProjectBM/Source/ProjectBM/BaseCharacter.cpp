// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HealthComponent.h"
#include "AttackComponent.h"
#include "ActionContextComponent.h"
#include "BasePlayerController.h"
#include "PCEntryInfo.h"

ABaseCharacter::ABaseCharacter()
	: Super()
{
	// 체력 관리 컴포넌트 추가
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// 공격 관리 컴포넌트 추가
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	ActionContextComponent = CreateDefaultSubobject<UActionContextComponent>(TEXT("ActionContextComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


bool ABaseCharacter::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	bool result = false;

	do
	{
		if (false == Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation))
		{
			break;
		}

		const ABasePlayerController* TargetPlayerController = Cast<ABasePlayerController>(RealViewer);
		const ABasePlayerController* OwnerPlayerController = Cast<ABasePlayerController>(Controller);

		if (nullptr == TargetPlayerController || nullptr == OwnerPlayerController)
		{
			break;
		}

		UPCEntryInfo* TargetEntryInfo = TargetPlayerController->PCEntryInfo;
		UPCEntryInfo* OwnerEntryInfo = OwnerPlayerController->PCEntryInfo;

		if (nullptr == TargetEntryInfo || nullptr == OwnerEntryInfo)
		{
			break;
		}

		if (TargetEntryInfo->GetSessionId() != OwnerEntryInfo->GetSessionId())
		{
			break;
		}

		result = true;

	} while (false);

	return result;
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 인터페이스 호출용
void ABaseCharacter::OnDeath_Implementation()
{

}

// 인터페이스 호출용
void ABaseCharacter::OnTakeDamage_Implementation()
{

}