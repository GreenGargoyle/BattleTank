// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::setThrottle(float throttle)
{
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttel: %f."), *name, throttle);

	//TODO clamp actual throttle value so player can't over-drive.
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

