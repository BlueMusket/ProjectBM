// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABaseGameMode(const FObjectInitializer& ObjectInitializer);
	virtual ~ABaseGameMode();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	virtual void InitGameState();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

	// 플레이어가 접속한 후 호출되는 함수
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
