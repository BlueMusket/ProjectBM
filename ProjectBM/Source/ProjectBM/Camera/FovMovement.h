// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraMovement.h"
#include "CameraMovementParam.h"
#include "FovMovement.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API UFovMovement : public UCameraMovement
{
	GENERATED_BODY()
	
public:
	virtual void Start(const FCameraMovementParam& Param);

	// Tick 함수 오버라이드
	virtual void HeartBeat(float DeltaTime, UCameraComponent* CameraComponent) override;
	// Tick 함수 오버라이드
	virtual bool IsFinish(UCameraComponent* CameraComponent) override;

public:
	// Map to store camera movement types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	int TargetFov;
};
