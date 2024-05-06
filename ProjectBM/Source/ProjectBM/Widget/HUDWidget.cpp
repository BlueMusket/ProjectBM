// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Internationalization/Text.h"

#include "../Camera/BasePlayerCameraManager.h"
#include "../Camera/CameraMovementParam.h"


void UHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (nullptr != ZoomInOutButton)
	{
		ZoomInOutButton->OnClicked.AddDynamic(this, &UHUDWidget::ZoomInOutButtonClicked);
	}

	IsZoomIn = true;
	SetText();
}


void UHUDWidget::ZoomInOutButtonClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController(); // 현재 플레이어 컨트롤러 가져오기

	ABasePlayerCameraManager* PlayerCameraManager = Cast<ABasePlayerCameraManager>(PlayerController->PlayerCameraManager);
	if (PlayerCameraManager)
	{
		FCameraMovementParam Param;

		if (true == IsZoomIn)
		{
			Param.MovementType = ECameraMovementType::CAMERA_MOVEMENT_TYPE_FOV;
			Param.ParamArray[0] = 100;
			Param.ParamArray[1] = 1;

			IsZoomIn = false;
		}
		else
		{
			
			Param.MovementType = ECameraMovementType::CAMERA_MOVEMENT_TYPE_FOV;
			Param.ParamArray[0] = 60;
			Param.ParamArray[1] = 1;

			IsZoomIn = true;
		}

		PlayerCameraManager->StartMovement(Param);
	}

	SetText();
}

void UHUDWidget::SetText()
{
	if (nullptr == ZoomText)
	{
		return;
	}

	if (true == IsZoomIn)
	{
		ZoomText->SetText(FText::FromString(TEXT("줌 아웃")));
	}
	else
	{

		ZoomText->SetText(FText::FromString(TEXT("줌 인")));
	}
}


void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}