// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;

/**
 * Responsible for driving the tank tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
	void intendMoveForward(float throwParam);

	UFUNCTION(BlueprintCallable, Category = Input)
	void intendTurnRight(float throwParam);

private:
	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;

	//Called from the pathfinding logic by the AI Controllers.
	virtual void RequestDirectMove(const FVector&, bool) override;
};
