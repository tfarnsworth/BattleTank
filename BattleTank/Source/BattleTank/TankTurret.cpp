// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	UE_LOG(LogTemp, Warning, TEXT("Rotating turret to %f"), NewRotation);
	SetRelativeRotation((FRotator(0, NewRotation, 0)));
}
