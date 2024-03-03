// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UWidgetContextComponent;
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

public:

	void UpdateHealthPercent(float HealthPercent);

	// EntryInfo 변경 시 호출될 함수
	UFUNCTION()
	void OnRep_EntryInfo();

public:
	void SetThrowMousePos(float X, float Y);
	void GetThrowMousePos(float& X, float& Y);

public: // widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UWidgetContextComponent* WidgetContext;

public:
	UPROPERTY(ReplicatedUsing = OnRep_EntryInfo, VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UPCEntryInfo* PCEntryInfo;
protected:
	// 리플리케이션 설정
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

private:
	float ThrowMousePosX;
	float ThrowMousePosY;
};
