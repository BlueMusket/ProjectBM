// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseProjectileMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent), ShowCategories = (Velocity))
class PROJECTBM_API UBaseProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
public:
	void RefreshPhysicsLinearVelocity();
	void TrajectorySimulating(const FVector& Location); // 발사체 궤적 시뮬레이션
};
