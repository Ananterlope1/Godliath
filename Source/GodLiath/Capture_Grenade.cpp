// Fill out your copyright notice in the Description page of Project Settings.


#include "Capture_Grenade.h"
#include "Capture_Actor.h"


void ACapture_Grenade::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle SpawnerHandle;
	FTimerDelegate SpawnerDelegate;
	SpawnerDelegate.BindUFunction( this, FName("GrenadeSpawn"));
	GetWorldTimerManager().SetTimer(SpawnerHandle, SpawnerDelegate, ActivateDelay, false);

}

void ACapture_Grenade::GrenadeSpawn()
{
    // Spawn the CaptureDevice

    // Destroy self
}
