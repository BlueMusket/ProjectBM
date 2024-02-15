// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EntryInfo.h"
#include "BaseGameInstance.generated.h"

class UConsoleCommand;
/**
 * 
 */
UCLASS()
class PROJECTBM_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

public:
	UFUNCTION(Exec)
	 void CommandSetSessionId(FString SessionIdStr);

public:
	CEntryInfo* GetEntryInfo() { return &EntryInfo; }

private:
	UConsoleCommand* ConsoleCommand;
	CEntryInfo EntryInfo;
};
