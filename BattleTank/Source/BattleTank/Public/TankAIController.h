// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void Tick(float) override;

	//How close can the AI Tank get to the player.
	float acceptanceRadius = 3000.0f;

public:
	virtual void BeginPlay() override;
};
