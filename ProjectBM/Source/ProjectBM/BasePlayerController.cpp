// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != BP_HUDWidget)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void ABasePlayerController::ShowRestartWidget()
{
	if (nullptr != BP_RestartWidget)
	{
		SetPause(true);
		SetInputMode(FInputModeGameAndUI());

		SetShowMouseCursor(true);
		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
}

void ABasePlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	SetPause(false);
	SetShowMouseCursor(false);
}

void ABasePlayerController::UpdateHealthPercent(float HealthPercent)
{
	if (nullptr != HUDWidget)
	{
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}
