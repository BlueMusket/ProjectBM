// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;
public:
	int GetCmdSessionId() { return CmdSessionId; }

public:
	UFUNCTION(Exec)
	void SetSessionId(FString SessionIdStr);

	UFUNCTION(Exec)
	void AdminWidget();

private:
	int CmdSessionId;
};
