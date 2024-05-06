// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

public:
	void UpdateHealthPercent(float HealthPercent);

protected:
	UFUNCTION()
	void ZoomInOutButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UButton* ZoomInOutButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ZoomText;

private:
	void SetText();

private:
	bool IsZoomIn;
};
