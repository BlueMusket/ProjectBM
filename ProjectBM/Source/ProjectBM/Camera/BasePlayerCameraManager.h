// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CameraMovementParam.h"
#include "BasePlayerCameraManager.generated.h"

class UCameraMovement;
class UCameraComponent;
class APlayerController;
/**
 * 
 */
UCLASS()
class PROJECTBM_API ABasePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	virtual void InitializeFor(class APlayerController* PC) override;

	// Tick 함수 오버라이드
	virtual void Tick(float DeltaTime) override;

public:
	void StartMovement(const FCameraMovementParam& Param);

public:
	// Map to store camera movement types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	TMap<int, UCameraMovement*> CameraMovements;

private:
	UCameraComponent* PcCamaraComponent;
	UCameraMovement* CurrentMovement;
};
