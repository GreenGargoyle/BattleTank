// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float crosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float crosshairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float lineTraceRange = 1000000;

	//Start the tank moving the barrell so that a shot would hit where the crosshair intersects the world.
	void aimTowardsCrosshair();

	//Return an OUT parameter, true if hit landscape.
	bool getSightRayHitLocation(FVector&) const;

	bool getLookDirection(FVector2D, FVector&) const;

	bool getLookVectorHitLocation(FVector, FVector&) const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void foundAimingComponent(UTankAimingComponent* aimingCompRef);

public:
	virtual void BeginPlay() override;

	virtual void Tick(float) override;
};
