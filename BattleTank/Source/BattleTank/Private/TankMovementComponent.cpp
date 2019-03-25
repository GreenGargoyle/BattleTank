// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}


void UTankMovementComponent::intendMoveForward(float throwParam)
{
	if (!leftTrack || !rightTrack) { return; }

	UE_LOG(LogTemp, Warning, TEXT("MOVE_FORWARD THROW: %f"), throwParam);

	leftTrack->setThrottle(throwParam);
	rightTrack->setThrottle(throwParam);

	//TODO - Prevent double speed due to dual control use.
}

void UTankMovementComponent::intendTurnRight(float throwParam)
{
	if (!leftTrack || !rightTrack) { return; }

	UE_LOG(LogTemp, Warning, TEXT("MOVE_RIGHT THROW: %f"), throwParam);

	leftTrack->setThrottle(throwParam);
	rightTrack->setThrottle(-throwParam);

	//TODO - Prevent double speed due to dual control use.
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as we're replacing the functionality here.

	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = moveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);

	intendMoveForward(forwardThrow);
}