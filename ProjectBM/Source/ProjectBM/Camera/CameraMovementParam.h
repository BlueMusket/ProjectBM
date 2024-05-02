// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraMovementParam.generated.h"



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
	
	TArray<int> ParamArray;
};
