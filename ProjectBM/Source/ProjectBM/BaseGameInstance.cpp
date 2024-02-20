// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "BasePlayerController.h"

void UBaseGameInstance::Init()
{
	Super::Init();
}

void UBaseGameInstance::SetSessionId(FString SessionIdStr)
{
	const int NewSessionId = FCString::Atoi(*SessionIdStr);

	CmdSessionId = NewSessionId;
}

void UBaseGameInstance::AdminWidget()
{
	UWorld* World = GetWorld();

	ABasePlayerController* PlayerController = World->GetFirstPlayerController<ABasePlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	PlayerController->ToggleAdminWidget();
}