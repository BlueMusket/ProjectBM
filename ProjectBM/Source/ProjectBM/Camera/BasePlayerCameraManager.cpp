// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCameraManager.h"
#include "CameraMovement.h"
#include "FovMovement.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

#include "../Controller/BasePlayerController.h"


void ABasePlayerCameraManager::InitializeFor(class APlayerController* PC)
{
	Super::InitializeFor(PC);

    ACharacter* PlayerCharacter = Cast<ACharacter>(PC->GetPawn());
    if (PlayerCharacter && PlayerCharacter->FindComponentByClass<UCameraComponent>())
    {
        PcCamaraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
    }

    CameraMovements.Add(1, NewObject<UFovMovement>());
}

void ABasePlayerCameraManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    if (nullptr != CurrentMovement)
    {
        CurrentMovement->HeartBeat(DeltaTime, PcCamaraComponent);

        if (true == CurrentMovement->IsFinish(PcCamaraComponent))
        {
            CurrentMovement = nullptr;
        }
    }
}

void ABasePlayerCameraManager::SetMovement(int Key)
{
    if (CameraMovements.Contains(Key))
    {
        CurrentMovement = CameraMovements[Key];
    }
}



void ABasePlayerCameraManager::StartMovement(const FCameraMovementParam& Param)
{

}

