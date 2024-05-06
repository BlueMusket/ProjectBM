// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCameraManager.h"
#include "CameraMovement.h"
#include "FovMovement.h"
#include "CameraMovementParam.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

#include "../Controller/BasePlayerController.h"


void ABasePlayerCameraManager::InitializeFor(class APlayerController* PC)
{
	Super::InitializeFor(PC);

    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CameraMovements.Add(ECameraMovementType::CAMERA_MOVEMENT_TYPE_FOV, NewObject<UFovMovement>());
}

void ABasePlayerCameraManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (nullptr == PcCamaraComponent)
    {
        ACharacter* PlayerCharacter = PCOwner->GetPawn<ACharacter>();
        if (PlayerCharacter && PlayerCharacter->FindComponentByClass<UCameraComponent>())
        {
            PcCamaraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
        }
    }

    if (nullptr == PcCamaraComponent)
    {
        return;
    }

    if (nullptr != CurrentMovement)
    {
        CurrentMovement->Heartbeat(DeltaTime, PcCamaraComponent);

        if (true == CurrentMovement->IsFinish(PcCamaraComponent))
        {
            CurrentMovement = nullptr;
        }
    }
}

void ABasePlayerCameraManager::StartMovement(FCameraMovementParam& Param)
{
    if (CameraMovements.Contains(Param.MovementType))
    {
        CurrentMovement = CameraMovements[Param.MovementType];

        CurrentMovement->Start(Param);
    }
}