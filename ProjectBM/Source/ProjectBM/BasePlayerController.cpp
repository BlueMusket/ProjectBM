// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"
#include "BaseCharacter.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	ENetRole MyLocalRole = GetLocalRole();
	ENetRole MyRemoteRole = GetRemoteRole();


}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FString SessionIdStr = FString::Printf(TEXT("SessionId : %d"), EntryInfo.GetSessionId());

	ABaseCharacter* BaseCharacter = GetPawn<ABaseCharacter>();

	if (!IsValid(BaseCharacter))
	{
		return;
	}

	FVector Location = BaseCharacter->GetActorLocation();

	if (true == IsLocalController()) // 서버
	{
		Location.Z += 10;
		DrawDebugString(GetWorld(), Location, SessionIdStr, nullptr, FColor::Red, 0.0f, true);
	}
	else // 클라이언트
	{
		DrawDebugString(GetWorld(), Location, SessionIdStr, nullptr, FColor::White, 0.0f, true);
	}
}


void ABasePlayerController::CreateHUD()
{
	if (nullptr != BP_HUDWidget)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		if (nullptr != HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void ABasePlayerController::ShowRestartWidget()
{
	//if (nullptr != BP_RestartWidget)
	//{
	//	SetPause(true);
	//	SetInputMode(FInputModeGameAndUI());

	//	SetShowMouseCursor(true);
	//	RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
	//	if (nullptr != RestartWidget)
	//	{
	//		RestartWidget->AddToViewport();
	//	}
	//}
}

void ABasePlayerController::HideRestartWidget()
{
	//RestartWidget->RemoveFromParent();
	//RestartWidget->Destruct();
	//SetPause(false);
	//SetShowMouseCursor(false);
}

void ABasePlayerController::UpdateHealthPercent(float HealthPercent)
{
	//if (nullptr != HUDWidget)
	//{
	//	HUDWidget->UpdateHealthPercent(HealthPercent);
	//}
}

void ABasePlayerController::SetSessionId(int32 NewSessionId)
{
	EntryInfo.SetSessionId(NewSessionId);
}

int ABasePlayerController::GetSessionId()
{
	return EntryInfo.GetSessionId();
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

void ABasePlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	CreateHUD();
}

