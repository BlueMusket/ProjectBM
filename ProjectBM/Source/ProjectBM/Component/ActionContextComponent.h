// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowParam.h"
#include "../Base/Lock.h"
#include "ActionContextComponent.generated.h"
/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTBM_API UActionContextComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActionContextComponent();
	virtual ~UActionContextComponent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitAction(int ActiveTick, FThrowParam& Param);
	void StartAction();

	bool GetIsActive() { return IsActive; }
	void DeActive() { IsActive = false; };
	void Active() { IsActive = true; };

	bool CheckCanAction();

public:

	// 서버에서만 호출
	void ServerStartThrowAction(FThrowParam Param);

private:
	FDateTime StartTime;
	bool IsActive;

	CLock Lock;
};