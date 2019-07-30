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
class AProjectile;

//Holds barrel's properties and elevate method.
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void moveBarrelTowards(FVector);

	bool isBarrelMoving();

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing) //EditDefaultsOnly - Can only edit it on all tanks via the blueprint. Can't edit it for individual tanks at runtime.
	float reloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint = nullptr;

	double lastFireTime = 0.0f;

	FVector aimDirection;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState firingState = EFiringState::Reloading;

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	void aimAt(FVector);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void fire();
};
