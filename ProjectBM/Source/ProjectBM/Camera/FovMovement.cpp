// Fill out your copyright notice in the Description page of Project Settings.


#include "FovMovement.h"
#include "Camera/CameraComponent.h"


void UFovMovement::Heartbeat(float DeltaTime, UCameraComponent* CameraComponent)
{
    float NewFOV = FMath::FInterpTo(CameraComponent->FieldOfView, TargetFov, DeltaTime, LerpSpeed);

    // 여기서부터는 도착으로 판단한다.
    if ( FMath::Abs(TargetFov - NewFOV) < 0.1f)
    {
        NewFOV = TargetFov;
    }

    CameraComponent->SetFieldOfView(NewFOV);
}


bool UFovMovement::IsFinish(UCameraComponent* CameraComponent)
{
    return TargetFov == CameraComponent->FieldOfView;
}


void UFovMovement::Start(FCameraMovementParam& Param)
{
    TargetFov = Param.ParamArray[0];
    LerpSpeed = Param.ParamArray[1];
}