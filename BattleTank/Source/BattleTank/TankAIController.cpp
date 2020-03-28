// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

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
    if (Tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank AI: %s"), *Tank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No AI tank found!"));
    }

    APawn* PlayerTank = GetPlayerTank();
    if (PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found player tank: %s"), *PlayerTank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No player tank found!"));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

APawn* ATankAIController::GetPlayerTank() const
{
    return GetWorld()->GetFirstPlayerController()->GetPawn();
}