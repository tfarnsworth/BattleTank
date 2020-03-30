// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (GetPlayerTank())
    {
        // TODO Move towards the player

        //Aim towards the player
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        //Fire if ready
    }
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    ATank* Tank = GetControlledTank();
    APawn* PlayerTank = GetPlayerTank();
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

APawn* ATankAIController::GetPlayerTank() const
{
    return GetWorld()->GetFirstPlayerController()->GetPawn();
}