// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "BasePlayerController.h"

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (nullptr != RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}
}

void URestartWidget::OnRestartClicked()
{
	ABasePlayerController* PlayerController = Cast< ABasePlayerController>(GetOwningPlayer());
	if (nullptr != PlayerController)
	{
		//PlayerController->HideRestartWidget();
	}

	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}
