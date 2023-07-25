// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "GodLiathGameModeBase.h"



void ABerserkerCharacter::BeginPlay()
{
	Super::BeginPlay();

	static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT("/Script/Engine.AnimSequence'/Game/ParagonRampage/Characters/Heroes/Rampage/Animations/Death_RiseFrom.Death_RiseFrom'"));
	ResurrectAnim = anim.Object;
}


float ABerserkerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Display, TEXT("Berserk Taking Damage"));
	
    if (IsDead())
	{
		UE_LOG(LogTemp, Warning, TEXT("Checking if dead"));
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
			GetWorldTimerManager().SetTimer(ResurrectTimer, this, &ABerserkerCharacter::PlayResurrection, ResurrectDelay);
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
	
	return Health <= 0;	

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

bool ABerserkerCharacter::IsTrueDead() const
{
	return TrueDeath;
}

void ABerserkerCharacter::PlayResurrection() const
{
	UE_LOG(LogTemp, Error, TEXT("Berserk Resurrection"));
	GetMesh()->PlayAnimation(ResurrectAnim, false);
	
}

