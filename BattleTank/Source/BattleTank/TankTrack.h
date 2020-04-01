// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);

    // Max force per track, in Newtons
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxDrivingForce = 400000.f; // Assume 40 ton tanks and 5m/s^2 acceleration
};
