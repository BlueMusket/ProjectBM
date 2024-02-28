// Fill out your copyright notice in the Description page of Project Settings.


#include "PCAnimInstance.h"
#include "Animation/AnimInstance.h"

void UPCAnimInstance::PlayThrow()
{
	if (nullptr == ThrowMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("ThrowMontage is null"));
		return;
	}

	bool bIsPlaying = Montage_IsPlaying(ThrowMontage);
	if (false == bIsPlaying)
	{
		Montage_Play(ThrowMontage, 1.0f);
	}
}

