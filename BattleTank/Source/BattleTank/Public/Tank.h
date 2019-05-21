// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankMovementComponent;
class UTankAimingComponent;
class AProjectile;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000.0f; 

	UPROPERTY(EditDefaultsOnly, Category = Firing) //EditDefaultsOnly - Can only edit it on all tanks via the blueprint. Can't edit it for individual tanks at runtime.
	float reloadTimeInSeconds = 3.0f;

	//Local barrel reference for spawning pprojectile.
	UTankBarrel* barrel = nullptr; //TODO - Remove.

	double lastFireTime = 0.0f;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* tankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* tankMovementComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();
	
	void aimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void fire();
};
