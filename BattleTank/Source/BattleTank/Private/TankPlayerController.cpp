// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = getControlledTank();

	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possesing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController posessing %s"), *(controlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	aimTowardsCrosshair();
}

ATank* ATankPlayerController::getControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::aimTowardsCrosshair()
{
	if (!getControlledTank())
	{
		return;
	}

	FVector hitLocation; //Out parameter.
	
	if (getSightRayHitLocation(hitLocation))
	{
		//If it hits the landscape.
			//Tell controlled tank to aim through crosshairs.
	}
	
}

//Get world location of linetrace through crosshair.
bool ATankPlayerController::getSightRayHitLocation(FVector& outHitLocation) const
{
	//Find the crosshair position.
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);

	FVector lookDirection;
	//"De-project" the screen position of the crosshair to a world direction.
	if (getLookDirection(screenLocation, lookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *lookDirection.ToString());
	}

	//Line-trace along the lookDirection, and see what we hit (up to max range).
	return false;
}

bool ATankPlayerController::getLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation; //To be discarded.
	FVector worldDirection;

	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}
