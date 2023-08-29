// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grenade.h"
#include "Capture_Grenade.generated.h"

/**
 * 
 */
UCLASS()
class GODLIATH_API ACapture_Grenade : public AGrenade
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void GrenadeSpawn();

private:

	UPROPERTY(EditAnywhere)
	ACapture_Actor* CaptureDevice;

	UPROPERTY(EditAnywhere)
	float ActivateDelay = 5;
	
};
