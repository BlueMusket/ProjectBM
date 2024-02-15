// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "GameFramework/PlayerController.h"
#include "Internationalization/Text.h"

void ULoginWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (nullptr != LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ULoginWidget::OnLoginClicked);
	}
}

void ULoginWidget::OnLoginClicked()
{
	APlayerController* PlayerController = Cast< APlayerController>(GetOwningPlayer());
	if (nullptr != PlayerController)
	{
		FText IpStr = ServerAddrTextBox->GetText();
		FString AddrCmd;
		//AddrCmd.Append("open ");
		AddrCmd.Append(IpStr.ToString());
		// 이후에 문서화 시킬것
		PlayerController->ClientTravel(AddrCmd, ETravelType::TRAVEL_Absolute);
		//PlayerController->ConsoleCommand(AddrCmd);
	}
}
