// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"
#include "BaseCharacter.h"
#include "PCEntryInfo.h"
#include "WidgetContextComponent.h"
#include "Net/UnrealNetwork.h"

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer/* = FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	// 리플리케이션 활성화
	bReplicates = true;
	WidgetContext = CreateDefaultSubobject<UWidgetContextComponent>(TEXT("WidgetContext"));

	// PCEntryInfo 인스턴스 생성 및 초기화
	//if (HasAuthority())
	{
		PCEntryInfo = NewObject<UPCEntryInfo>();
	}
}

void ABasePlayerController::Deserialize(int NewSessionId, int NewPartyId, int NewUserId)
{
	PCEntryInfo->Deserialize(NewSessionId, NewPartyId, NewUserId);
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();


	//ENetRole MyLocalRole = GetLocalRole();
	//ENetRole MyRemoteRole = GetRemoteRole();
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != PCEntryInfo)
	{
		const FString SessionIdStr = FString::Printf(TEXT("SessionId : %d"), PCEntryInfo->GetSessionId());

		ABaseCharacter* BaseCharacter = GetPawn<ABaseCharacter>();

		if (!IsValid(BaseCharacter))
		{
			return;
		}

		FVector Location = BaseCharacter->GetActorLocation();

		ENetRole MyLocalRole = GetLocalRole();

		if (ENetRole::ROLE_Authority == MyLocalRole) // 서버
		{
			Location.Z += 10;
			DrawDebugString(GetWorld(), Location, SessionIdStr, nullptr, FColor::Red, 0.0f, true);
		}
		else // 클라이언트
		{
			DrawDebugString(GetWorld(), Location, SessionIdStr, nullptr, FColor::White, 0.0f, true);
		}
	}
}

void ABasePlayerController::UpdateHealthPercent(float HealthPercent)
{
	//if (nullptr != HUDWidget)
	//{
	//	HUDWidget->UpdateHealthPercent(HealthPercent);
	//}
}

void ABasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// EntryInfo의 리플리케이션 설정
	DOREPLIFETIME(ABasePlayerController, PCEntryInfo);
}

// Server only
void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//AGDPlayerState* PS = GetPlayerState<AGDPlayerState>();
	//if (PS)
	//{
	//	// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
	//	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	//}
}


void ABasePlayerController::OnRep_EntryInfo()
{

}

void ABasePlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	// CreateHUD();
}

