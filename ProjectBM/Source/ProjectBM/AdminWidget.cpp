// Fill out your copyright notice in the Description page of Project Settings.


#include "AdminWidget.h"
#include "BasePlayerController.h"
#include "BaseGameInstance.h"
#include "Components/Button.h"

void UAdminWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (nullptr != JoinServerButton)
	{
		JoinServerButton->OnClicked.AddDynamic(this, &UAdminWidget::OnJoinServerClicked);
	}
}

void UAdminWidget::OnJoinServerClicked()
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
	{
		UBaseGameInstance* GameInstance = World->GetGameInstance<UBaseGameInstance>();
		if (nullptr == GameInstance)
		{
			return;
		}

		int NewSessionId = GameInstance->GetCmdSessionId();
		int NewPartyId = 0;
		int NewUserId = 0;

		//FString option = TEXT("?SessionId=%d, PartyId=%d, UserId=%d", NewSessionId, NewPartyId, NewUserId);
		//FString levelName = L"127.0.0.1:17777";
		//UGameplayStatics::OpenLevel(World, *levelName, true, option);
	}
}