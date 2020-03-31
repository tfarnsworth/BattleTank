// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) const
{
	if (!Barrel|| !Turret) { return; }

	FVector Out_TossVelocity(0);
	bool bAimSuccess = UGameplayStatics::SuggestProjectileVelocity(
		this,
		Out_TossVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bAimSuccess)
	{
		auto AimDirection = Out_TossVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("Aim solution found: %s"), *AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No aim solution found"));
	}
}


void UTankAimingComponent::MoveBarrel(FVector AimDirection) const
{
	if (!Barrel) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection) const
{
	if (!Turret) { return; }
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotation;
	Turret->Rotate(DeltaRotator.Yaw);
}
