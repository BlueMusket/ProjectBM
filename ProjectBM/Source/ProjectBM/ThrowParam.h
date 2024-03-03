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
	bool Serialize(APC* PC);

public:
	UPROPERTY(EditAnywhere, Category = Projectile)
	float MaxPower;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float PowerIncreaseRate;

	UPROPERTY(EditAnywhere, Category = Projectile)
	FVector SpawnLocation; // 투사체 생성 위치

	UPROPERTY(EditAnywhere, Category = Projectile)
	FRotator ThrowRotation; // 투사체 발사 방향

	UPROPERTY(EditAnywhere, Category = Projectile)
	float ThrowPower; // 투사체 발사 파워

	UPROPERTY()
	bool IsValid; // 유효한 정보인지
};
