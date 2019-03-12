// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect points as added as construction.
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::setBarrelReference(UTankBarrel* barrelToSet)
{
	tankAimingComponent->setBarrelReference(barrelToSet);

	//Local reference.
	barrel = barrelToSet;
}

void ATank::setTurretReference(UTankTurret* turretToSet)
{
	tankAimingComponent->setTurretReference(turretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::aimAt(FVector hitLocation)
{
	tankAimingComponent->aimAt(hitLocation, launchSpeed);
}

void ATank::fire()
{
	if (!barrel) { return; }

	//Spawn projectile at location of socket barrel.
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
		projectileBlueprint, 
		barrel->GetSocketLocation(FName("Projectile")),
		barrel->GetSocketRotation(FName("Projectile"))
		);

	projectile->launchProjectile(launchSpeed);
}

