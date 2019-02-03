// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float crosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float crosshairYLocation = 0.3333;

	//Start the tank moving the barrell so that a shot would hit where the crosshair intersects the world.
	void aimTowardsCrosshair();

	//Return an OUT parameter, true if hit landscape.
	bool getSightRayHitLocation(FVector&) const;

	bool getLookDirection(FVector2D, FVector&) const;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	ATank* getControlledTank() const;
};
