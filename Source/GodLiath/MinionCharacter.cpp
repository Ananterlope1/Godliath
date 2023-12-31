// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GodLiathGameModeBase.h"
#include "MeleeWeapon.h"


void AMinionCharacter::BeginPlay()
{
	Super::BeginPlay();
}

float AMinionCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageToApply;
	
    if (IsDead())
	{
		UE_LOG(LogTemp, Error, TEXT("Minion Dead"));
		Eatable = true;
		// Need to set this after being eaten or it stops checks on this minion.
        // DetachFromControllerPendingDestroy();		
		
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		AGodLiathGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGodLiathGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
            
		}
	}

	return DamageToApply;
}

bool AMinionCharacter::IsDead() 
{	
	if(this->IsPendingKillPending())
	{		
		return true;
	}
	return Health <= 0;
}


