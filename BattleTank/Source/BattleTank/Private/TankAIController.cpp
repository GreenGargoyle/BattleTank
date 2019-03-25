// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* controlledTank = Cast<ATank>(GetPawn());

	if (playerTank)
	{
		//TODO Move towards player.
		MoveToActor(playerTank, acceptanceRadius); //TODO - Check radius is in centimetres.

		//Aim towards the player.
		controlledTank->aimAt(playerTank->GetActorLocation());

		controlledTank->fire(); //TODO - Don't fire every frame.
	}
	
}




