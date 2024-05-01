// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "Controller/BasePlayerController.h"
#include "Effect/EffectManager.h"

void UBaseGameInstance::Init()
{
	Super::Init();

	// 데이터 초기화 로드를 멀티쓰레드로 할지 고민좀
	UEffectManager::Get()->Init();
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

	//PlayerController->ToggleAdminWidget();
}