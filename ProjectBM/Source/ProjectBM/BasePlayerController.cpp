// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	ENetRole MyLocalRole = GetLocalRole();
	ENetRole MyRemoteRole = GetRemoteRole();


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

