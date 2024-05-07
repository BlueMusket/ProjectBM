// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTBM_API FinishSimulateOrigin
{
public:
	FinishSimulateOrigin();
	~FinishSimulateOrigin();

public:
	// 시작 위치
	FVector SpawnLocation;
	// 파워
	int Power;
	// 각도
	FRotator Rotation;

	// 투사체 데미지
	int Damage;

	// 투사체 반지름
	int Radius;

	// 이펙트 충돌 박스
	FVector CollisionSize;
};
