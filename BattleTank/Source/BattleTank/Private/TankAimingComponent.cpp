// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	//So first fire is after initial reload.
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	barrel = barrelToSet;
	turret = turretToSet;
}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(barrel)) { return false; }

	FVector barrelForward = barrel->GetForwardVector();

	return !barrelForward.Equals(aimDirection, 0.01);
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingState = EFiringState::Reloading;
	}
	else if (isBarrelMoving())
	{
		firingState = EFiringState::Aiming;
	}
	else
	{
		firingState = EFiringState::Locked;
	}
}


void UTankAimingComponent::aimAt(FVector hitLocation)
{
	if (!ensure(barrel)) 
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

	if (bHaveAimSolution)
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		moveBarrelTowards(aimDirection);
	}
	//No aim solution found.
}

void UTankAimingComponent::moveBarrelTowards(FVector aimDirection)
{
	if (!ensure(barrel) || !ensure(turret)) 
	{ 
		return; 
	}

	//Work out difference between current barrel rotation and aimDirection.
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotator;

	barrel->elevate(deltaRotator.Pitch); 
	turret->rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::fire()
{
	if (firingState != EFiringState::Reloading)
	{
		if (!ensure(barrel)) { return; }
		if (!ensure(projectileBlueprint)) { return; }

		//Spawn projectile at location of socket barrel.
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->launchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}

