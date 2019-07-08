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
	if (!ensure(leftTrack && rightTrack)) { return; }

	leftTrack->setThrottle(throwParam);
	rightTrack->setThrottle(throwParam);
}

void UTankMovementComponent::intendTurnRight(float throwParam)
{
	if (!ensure(leftTrack && rightTrack)) { return; }

	leftTrack->setThrottle(throwParam);
	rightTrack->setThrottle(-throwParam);
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as we're replacing the functionality here.

	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = moveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	intendMoveForward(forwardThrow);

	float rightThrow = FVector::CrossProduct(tankForward, aiForwardIntention).Z;
	intendTurnRight(rightThrow);
}