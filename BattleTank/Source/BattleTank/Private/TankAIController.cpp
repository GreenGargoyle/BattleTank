// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto playerTank = getPlayerTank();

	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController can't find player tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player: %s"), *(playerTank->GetName()));
	}
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (getPlayerTank())
	{
		//TODO Move towards player.

		//Aim towards the player.
		getControlledTank()->aimAt(getPlayerTank()->GetActorLocation());

		//Fire if ready.
	}
	
}

ATank* ATankAIController::getControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::getPlayerTank() const
{
	auto playerPawn = (GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!playerPawn)
	{
		return nullptr;
	}

	return Cast<ATank>(playerPawn);
}


