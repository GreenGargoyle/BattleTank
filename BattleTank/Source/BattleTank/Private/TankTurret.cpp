// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void  UTankTurret::rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);

	float rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0.0f, rotation, 0.0f));
}


