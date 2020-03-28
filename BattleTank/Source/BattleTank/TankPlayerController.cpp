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
    if (!GetControlledTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("No tank found!"));
        return;
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
    bool Hit = GetSightRayHitLocation(Out_HitLocation);
    if (Hit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit at %s"), *Out_HitLocation.ToString());
        GetControlledTank()->AimAt(Out_HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& Out_HitLocation) const
{
    // Find the crosshair position
    int32 Out_ViewportSizeX, Out_ViewportSizeY;
    GetViewportSize(Out_ViewportSizeX, Out_ViewportSizeY);
    float ScreenLocationX = Out_ViewportSizeX * CrosshairXLocation;
    float ScreenLocationY = Out_ViewportSizeY * CrosshairYLocation;
    FVector2D ScreenLocation
    (
        ScreenLocationX,
        ScreenLocationY
    );
    // De-project the screen position of the crosshair to a world direction
    FVector Out_LookDirection;
    if (GetLookDirection(ScreenLocation, Out_LookDirection))
    {
        // Line-trace along that look direction, and see what we hit (up to a max range)    
        if (GetLookVectorHitLocation(Out_LookDirection, Out_HitLocation))
        {
            return true;
        }
    }


    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& Out_LookDirection) const
{
    FVector Out_WorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        Out_WorldLocation,
        Out_LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& Out_HitLocation) const
{
    FHitResult Out_HitResult;
    auto Start = PlayerCameraManager->GetCameraLocation();
    auto End = Start + (LookDirection * LineTraceRange);
    auto QueryParams = FCollisionQueryParams();
    auto CollisionResponseParams = FCollisionResponseParams();
    bool HitSuccess = GetWorld()->LineTraceSingleByChannel(
        Out_HitResult,
        Start,
        End,
        ECollisionChannel::ECC_Visibility,
        QueryParams,
        CollisionResponseParams
    );
    if (HitSuccess)
    {
        Out_HitLocation = Out_HitResult.Location;
    }
    return HitSuccess;
}




