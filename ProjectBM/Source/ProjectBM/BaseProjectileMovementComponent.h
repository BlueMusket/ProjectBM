// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseProjectileMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API UBaseProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
public:
	void RefreshPhysicsLinearVelocity();
};
