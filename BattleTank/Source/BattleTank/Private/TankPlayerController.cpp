// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


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
	if (!getControlledTank)
	{
		return;
	}

	//Get world location if linetrace through crosshair.
	//If it hits the landscape.
		//Tell controlled tank to aim through crosshairs.
}

