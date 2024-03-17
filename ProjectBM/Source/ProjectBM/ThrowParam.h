// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThrowParam.generated.h"

class APC;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FThrowParam
{
	GENERATED_USTRUCT_BODY()

public:
	FThrowParam();
	~FThrowParam();

public:
	bool IsValid();
public:
	
	UPROPERTY()
	FRotator ThrowRotation; // 투사체 발사 방향

	UPROPERTY()
	float ThrowPower; // 투사체 발사 파워
};
