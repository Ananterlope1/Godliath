// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GodLiathGameModeBase.h"





float ABerserkerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
    if (IsDead())
	{
		if (TrueDeath)
		{
			UE_LOG(LogTemp, Display, TEXT("IsTrueDeath Berserker"));
			DetachFromControllerPendingDestroy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
			AGodLiathGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGodLiathGameModeBase>();
			if (GameMode != nullptr)
			{
				GameMode->PawnKilled(this);
			}
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("Resurrecting Berserker Health!"));
			DamageToApply = -MaxHealth;
		}		
		
	}

	return DamageToApply;
}

void ABerserkerCharacter::Tick(float DeltaTime)
{
	//Add check for berserkers size/ scale then add tag to move (unlock) the snow pile
	// Might be able to add after the eat event rather than on tick. Save resources
}

bool ABerserkerCharacter::IsDead() const
{
	if (TrueDeath)
	{
		return Health <= 0;
	}
	
	return false;	

}

bool ABerserkerCharacter::Eat()
{
    // Get object to eat
    // Despawn object
    // Increase berserker character scale by value
	// Check boolean selector for dead enemy in range. 
	// BTService for enemy dead/eatable location
	// BTTask for eat with animation and gibs

	return true;
}
