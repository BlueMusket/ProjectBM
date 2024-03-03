// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectileMovementComponent.h"

void UBaseProjectileMovementComponent::RefreshPhysicsLinearVelocity()
{
	if (bInitialVelocityInLocalSpace)
	{
		SetVelocityInLocalSpace(Velocity);
	}

	if (bRotationFollowsVelocity)
	{
		if (UpdatedComponent)
		{
			FRotator DesiredRotation = Velocity.Rotation();
			if (bRotationRemainsVertical)
			{
				DesiredRotation.Pitch = 0.0f;
				DesiredRotation.Yaw = FRotator::NormalizeAxis(DesiredRotation.Yaw);
				DesiredRotation.Roll = 0.0f;
			}

			UpdatedComponent->SetWorldRotation(DesiredRotation);
		}
	}

	UpdateComponentVelocity();

	if (UpdatedPrimitive && UpdatedPrimitive->IsSimulatingPhysics())
	{
		UpdatedPrimitive->SetPhysicsLinearVelocity(Velocity);
	}
}