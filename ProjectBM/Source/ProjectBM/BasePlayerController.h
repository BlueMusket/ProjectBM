// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EntryInfo.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	// PlayerState 세팅 반응
	virtual void OnRep_PlayerState() override;
public:
	void CreateHUD();
	void ShowRestartWidget();
	void HideRestartWidget();
	void UpdateHealthPercent(float HealthPercent);

public:
	void SetSessionId(int32 NewSessionId);
	int GetSessionId();
	CEntryInfo* GetEntryInfo() { return &EntryInfo; }

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

private:
	UPROPERTY()
	class URestartWidget* RestartWidget;

	UPROPERTY()
	class UHUDWidget* HUDWidget;

private:
	CEntryInfo EntryInfo;
};
