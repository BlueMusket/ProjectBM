// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMovementParam.h"


FCameraMovementParam::FCameraMovementParam()
	:MovementType(ECameraMovementType::CAMERA_MOVEMENT_TYPE_MAX)
{
	ParamArray.Init(0, INT_PARAM_MAX);
}

FCameraMovementParam::~FCameraMovementParam()
{

}