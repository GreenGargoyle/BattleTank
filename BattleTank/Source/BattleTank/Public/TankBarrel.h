// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDegreesPerSecond = 10.0f; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxElevationDegrees = 40.0f; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float minElevationDegrees = 0.0f;

public:
	//-1 is max downward speed, and +1 is max upward speed.
	void elevate(float);
};
