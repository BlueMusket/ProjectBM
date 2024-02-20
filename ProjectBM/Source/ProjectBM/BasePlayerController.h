// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UPCEntryInfo;
/**
 * 
 */
UCLASS()
class PROJECTBM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Deserialize(int NewSessionId, int NewPartyId, int NewUserId);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	// PlayerState 세팅 반응
	virtual void OnRep_PlayerState() override;

public: // widget
	void CreateHUD();
	void ShowRestartWidget();
	void HideRestartWidget();
	void ToggleAdminWidget();


public:
	void UpdateHealthPercent(float HealthPercent);

	// EntryInfo 변경 시 호출될 함수
	UFUNCTION()
	void OnRep_EntryInfo();

public: // widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UAdminWidget> BP_AdminWidget;

private: // widget
	UPROPERTY()
	class URestartWidget* RestartWidget;

	UPROPERTY()
	class UHUDWidget* HUDWidget;

	UPROPERTY()
	class UAdminWidget* AdminWidget;

public:
	UPROPERTY(ReplicatedUsing = OnRep_EntryInfo, VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UPCEntryInfo* PCEntryInfo;
protected:
	// 리플리케이션 설정
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;


};
