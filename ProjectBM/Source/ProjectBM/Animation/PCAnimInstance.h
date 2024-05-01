// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimInstance.h"
#include "PCAnimInstance.generated.h"

class UAnimMontage;
/**
 * 
 */
UCLASS()
class PROJECTBM_API UPCAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void PlayThrow() override;

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* ThrowMontage;
};
