// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"
#include "EntryBuilder.h"
#include "../Controller/BasePlayerController.h"

ABaseGameMode::ABaseGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

ABaseGameMode::~ABaseGameMode()
{

}

void ABaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
}

void ABaseGameMode::InitGameState()
{
    Super::InitGameState();
}

void ABaseGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* ABaseGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    APlayerController* BaseController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

    do
    {
        ABasePlayerController* NewPlayerController = Cast<ABasePlayerController>(BaseController);

        if (!IsValid(NewPlayerController))
        {
            break;
        }

        CEntryBuilder Builder(NewPlayerController);
        Builder.Build(Options);


    } while (false);

    return BaseController;
}


void ABaseGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // 새로운 플레이어 접속 처리
    if (nullptr == NewPlayer)
    {
        return;
    }

	UE_LOG(LogTemp, Log, TEXT("플레이어가 게임에 접속했습니다: %s"), *NewPlayer->GetName());
}