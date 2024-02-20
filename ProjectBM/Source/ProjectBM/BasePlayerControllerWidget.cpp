// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"
#include "AdminWidget.h"


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

void ABasePlayerController::ToggleAdminWidget()
{
	if (nullptr != BP_AdminWidget)
	{
		if (nullptr == AdminWidget)
		{
			AdminWidget = CreateWidget<UAdminWidget>(this, BP_AdminWidget);
		}

		if (true == AdminWidget->IsVisible())
		{
			AdminWidget->RemoveFromParent();
		}
		else
		{
			AdminWidget->AddToViewport();
		}
	}
}