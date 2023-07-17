// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GodLiathGameModeBase.h"





float ABerserkerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
    if (IsDead())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		AGodLiathGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGodLiathGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
	}

	return DamageToApply;
}
