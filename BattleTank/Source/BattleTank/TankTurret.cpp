// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation((FRotator(0, Rotation, 0)));
}
