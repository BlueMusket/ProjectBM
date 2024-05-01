// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AdminWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API UAdminWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
	void OnJoinServerClicked();

public:
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* JoinServerButton;
};
