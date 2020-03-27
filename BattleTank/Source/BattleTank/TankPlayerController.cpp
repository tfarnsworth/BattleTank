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

    FVector Out_HitLocation; // Out parameter
    // Get world location if linetrace through crosshair
    // If it hits the landscape
        // Tell controlled tank to aim at this point
    bool Hit = GetSightRayHitLocation(Out_HitLocation);
    if (Hit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit at %s"), *Out_HitLocation.ToString());;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No hit"));
    }

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& Out_HitLocation) const
{
    FCollisionQueryParams TraceParams(
        FName(TEXT("")),
        false,
        GetOwner()
    );

    return GetWorld()->LineTraceSingleByObjectType(
        Out_HitLocation,
        GetTankWorldPosition(),
        GetTankRange(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParams
    );
}

FVector ATankPlayerController::GetTankWorldPosition() const
{
    FVector Out_PlayerLocation;
    FRotator Out_PlayerRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        Out_PlayerLocation,
        Out_PlayerRotation
    );
    return Out_PlayerLocation;
}

FVector ATankPlayerController::GetTankRange() const
{
    // Get the player's viewpoint
    FVector Out_PlayerLocation;
    FRotator Out_PlayerRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Out_PlayerLocation, Out_PlayerRotation);

    //Draw a line from the player showing the reach.

    return Out_PlayerLocation + Out_PlayerRotation.Vector() * 10000.f;
}




