// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkerCharacter.h"

// Sets default values
ABerserkerCharacter::ABerserkerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABerserkerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
}

// Called every frame
void ABerserkerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABerserkerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABerserkerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health Left: %f"), Health);
	
	return DamageToApply;

}

bool ABerserkerCharacter::IsDead() const
{	
	return Health <= 0;
}