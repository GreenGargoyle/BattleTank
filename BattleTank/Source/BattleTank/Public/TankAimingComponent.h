// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for aiming state.
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward declaration.
class UTankTurret;
class UTankBarrel; 

//Holds barrel's properties and elevate method.
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000.0f;

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void moveBarrelTowards(FVector);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState firingState = EFiringState::Reloading;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	void aimAt(FVector);
};
