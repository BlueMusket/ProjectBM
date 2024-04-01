// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PCState.generated.h"

class CActionContext;
/**
 * 
 */
UCLASS()
class PROJECTBM_API APCState : public APlayerState
{
	GENERATED_BODY()

public:
	APCState();
	virtual ~APCState();

public:
	// 타이머를 시작하는 함수
	virtual void BeginPlay() override;

public:
	void StartTimer();
	void Tick();
private:

	// 타이머 핸들
	FTimerHandle TimerHandle;

	CActionContext* ActionContext;

};
