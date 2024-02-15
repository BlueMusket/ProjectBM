// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMatchWidget.h"
#include "Components/Button.h"
#include "BasePlayerController.h"

void ULobbyMatchWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (nullptr != LobbyMatchButton)
	{
		LobbyMatchButton->OnClicked.AddDynamic(this, &ULobbyMatchWidget::OnMatchClicked);
	}
}

void ULobbyMatchWidget::OnMatchClicked()
{
	ABasePlayerController* PlayerController = Cast< ABasePlayerController>(GetOwningPlayer());
	if (nullptr != PlayerController)
	{
		//FText IpStr = ServerAddrTextBox.GetText();
		//FString AddrCmd;
		//AddrCmd.Append("Open ");
		//AddrCmd.Append(ipStr.ToString());
		//// 이후에 문서화 시킬것

		//PlayerController->ConsoleCommand(AddrCmd);
	}
}
