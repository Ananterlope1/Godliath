// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SetTag_OnScaleOverlapped.generated.h"

UCLASS()
class GODLIATH_API ASetTag_OnScaleOverlapped : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASetTag_OnScaleOverlapped();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tagging")
	FName TagToAdd;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tagging")
	double ScaleToAddTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tagging")
	FName TagToCheckFor = "MainBerserk";

private:

	AActor* GetAcceptableActor() const;

};
