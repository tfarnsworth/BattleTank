// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (PlayerTank)
    {
        // TODO Move towards the player

        //Aim towards the player
        auto ControlledTank = Cast<ATank>(GetPawn());
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        //Fire every frame;
        ControlledTank->Fire();
    }
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}