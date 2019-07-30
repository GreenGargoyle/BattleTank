// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() 
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm hit."));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Calculate the slippage speed.
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work out the required acceleration this frame to correct.
	FVector correctionAcceleration = -slippageSpeed / DeltaTime  * GetRightVector();

	//Calculate and apply sideways force (F = ma).
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2; //Two tracks.

	tankRoot->AddForce(correctionForce);
}


void UTankTrack::setThrottle(float throttle)
{
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	auto* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

