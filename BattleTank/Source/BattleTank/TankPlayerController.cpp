// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    ATank* Tank = GetControlledTank();
    if (Tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("We have a tank: %s"), *Tank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No tank found!"));
    }
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }
    // Get world location if linetrace through crosshair
    // If it hits the landscape
        // Tell controlled tank to aim at this point
}


