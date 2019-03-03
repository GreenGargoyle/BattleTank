// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO - Should this really tick?

	// ...
}

void UTankAimingComponent::setBarrelReference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::aimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel) 
	{
		return;
	}

	FVector outLaunchVelocity(0);
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the outLaunchVelocity.
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	float time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		moveBarrelTowards(aimDirection);

		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found."), time);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found."), time);
	}
}

void UTankAimingComponent::moveBarrelTowards(FVector aimDirection)
{
	//Work out difference between current barrel rotation and aimDirection.
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;

	barrel->elevate(deltaRotator.Pitch); 
}