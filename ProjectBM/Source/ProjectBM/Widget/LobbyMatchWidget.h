// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMatchWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API ULobbyMatchWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
	void OnMatchClicked();
public:
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
		class UButton* LobbyMatchButton;
};
