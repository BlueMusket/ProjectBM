// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraMovementParam.generated.h"


UENUM()
enum class ECameraMovementType : uint8
{
	CAMERA_MOVEMENT_TYPE_FOV = 0,
	CAMERA_MOVEMENT_TYPE_MAX,
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCameraMovementParam
{
	GENERATED_USTRUCT_BODY()

public:
	FCameraMovementParam();
	~FCameraMovementParam();

public:
	static const int INT_PARAM_MAX = 5;

public:
	ECameraMovementType MovementType;
	TArray<int> ParamArray;
};
