// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
	void OnLoginClicked();

public:
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* LoginButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UEditableTextBox* ServerAddrTextBox;
};
