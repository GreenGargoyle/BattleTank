// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void  UTankBarrel::elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);

	//Move the barrel the right amount this frame given a max elevation speed and the frame time.
	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called: %f"), relativeSpeed);

	float elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float elevation = FMath::Clamp<float>((RelativeRotation.Pitch + elevationChange), minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0.0f, 0.0f));
}
