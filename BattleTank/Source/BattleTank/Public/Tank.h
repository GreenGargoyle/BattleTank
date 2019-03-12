// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 4000.0f; 

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint = nullptr; 

	//Local barrel reference for spawning pprojectile.
	UTankBarrel* barrel = nullptr;

protected:
	UTankAimingComponent* tankAimingComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setBarrelReference(UTankBarrel* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTurretReference(UTankTurret* turretToSet);
	
	void aimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void fire();
};
