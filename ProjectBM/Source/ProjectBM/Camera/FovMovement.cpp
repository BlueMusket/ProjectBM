// Fill out your copyright notice in the Description page of Project Settings.


#include "FovMovement.h"
#include "Camera/CameraComponent.h"


void UFovMovement::HeartBeat(float DeltaTime, UCameraComponent* CameraComponent)
{

}


bool UFovMovement::IsFinish(UCameraComponent* CameraComponent)
{
    return true;
}


void UFovMovement::Start(const FCameraMovementParam& Param)
{
    TargetFov = Param.ParamArray[0];
}