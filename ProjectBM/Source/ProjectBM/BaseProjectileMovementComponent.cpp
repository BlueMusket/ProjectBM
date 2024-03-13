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

void UBaseProjectileMovementComponent::TrajectorySimulating(const FVector& Location)
{

	static float gap = 1.0f;
	static float test = 100;
	FVector OldVelocity = Velocity;
	FVector OldLocation = Location;

	for (float step = 0.f; step < test; step += 1.f * gap)
	{
		const FVector MoveDelta = ComputeMoveDelta(OldVelocity, step);
		OldVelocity = ComputeVelocity(OldVelocity, step);

		FVector NewLocation = OldLocation + MoveDelta;
		DrawDebugSphere(GetWorld(), NewLocation, 10.0f, 5, FColor::Red, false, 5.0f);
		OldLocation = NewLocation;
	}
}