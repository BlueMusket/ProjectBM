// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void PlayThrow();
};
