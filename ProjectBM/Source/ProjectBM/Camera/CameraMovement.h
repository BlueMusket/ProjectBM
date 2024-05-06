// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraMovementParam.h"
#include "CameraMovement.generated.h"


class UCameraComponent;
/**
 * 
 */
UCLASS()
class PROJECTBM_API UCameraMovement : public UObject
{
	GENERATED_BODY()

public:
	virtual void Start(FCameraMovementParam& Param);
		// Tick 함수 오버라이드
	virtual void Heartbeat(float DeltaTime, UCameraComponent* CameraComponent);
	
	virtual bool IsFinish(UCameraComponent* CameraComponent);
};