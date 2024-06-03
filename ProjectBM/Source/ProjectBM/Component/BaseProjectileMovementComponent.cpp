// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectileMovementComponent.h"


//#if UE_EDITOR
//PRAGMA_DISABLE_OPTIMIZATION
//#endif

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

void UBaseProjectileMovementComponent::TrajectorySimulating(const FVector& Location)
{
	static float deltaTick = 0.3f;
	FVector OldVelocity = Velocity;
	FVector OldLocation = Location;

	for (int i = 0; i < 50; ++i)
	{
		const FVector MoveDelta = ComputeMoveDelta(OldVelocity, deltaTick);
		OldVelocity = ComputeVelocity(OldVelocity, deltaTick);

		FVector NewLocation = OldLocation + MoveDelta;
		DrawDebugSphere(GetWorld(), NewLocation, 10.0f, 5, FColor::Red, false, 5.0f);
		OldLocation = NewLocation;
	}
}