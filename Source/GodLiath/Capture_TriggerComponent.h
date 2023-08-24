// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Capture_TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODLIATH_API UCapture_TriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UCapture_TriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UFUNCTION()
	// void OnOverlapBegin(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// UFUNCTION()
	// void OnOverlapEnd(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// ABerserkerCharacter* GetAcceptableActor() const;


};
