// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAimingComponent.h"
//Depends on movement component via pathfinding system.

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	APawn* playerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	APawn* controlledTank = GetPawn();

	if (!ensure(playerTank && controlledTank)) { return; }

	//TODO Move towards player.
	UTankAimingComponent* aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	MoveToActor(playerTank, acceptanceRadius); //TODO - Check radius is in centimetres.

	//Aim towards the player.
	aimingComponent->aimAt(playerTank->GetActorLocation());

	//TODO - Fix firing.
	//controlledTank->fire(); //TODO - Don't fire every frame.
}




