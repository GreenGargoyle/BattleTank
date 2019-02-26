// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegreesPerSecond = 20.0f; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float maxElevationDegrees = 40.0f; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float minElevationDegrees = 0.0f;

public:
	void elevate(float degreesPerSecond);
};
