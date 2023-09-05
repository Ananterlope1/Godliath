// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "GodLiathGameModeBase.h"
#include "MeleeWeapon.h"
#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


void ABerserkerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


float ABerserkerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Display, TEXT("Berserk Taking Damage"));
	Health -= DamageToApply;
	
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
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			UE_LOG(LogTemp, Error, TEXT("Count to 5 resurrect!"));
			FTimerHandle ResurrectHandle;
			FTimerDelegate ResurrectDelegate;
			ResurrectDelegate.BindUFunction( this, FName("PlayResurrection"));
			GetWorldTimerManager().SetTimer(ResurrectHandle, ResurrectDelegate, ResurrectDelay, false);	
			// GetWorldTimerManager().SetTimer(ResurrectTimer, this, &ABerserkerCharacter::PlayResurrection, ResurrectDelay, false);
			UE_LOG(LogTemp, Warning, TEXT("Resurrecting Berserker Health!"));
			
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			
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

void ABerserkerCharacter::Eat()
{
    // Get object to eat
    // Despawn object
    // Increase berserker character scale by value 
	// BTService for enemy dead/eatable location
	// BTTask for eat with animation and gibs
	if (EatSound)
	{
	UGameplayStatics::SpawnSoundAttached(EatSound, GetMesh(), TEXT("Status"));
	}	

	Eating = true;
	FVector CurrentScale = this->GetActorScale3D();
	CurrentScale *= ScalingEating;
	this->SetActorScale3D(CurrentScale);
	if (CurrentScale.X >= CargoOpenScale.X)
	{
		this->Tags.AddUnique(FName(TEXT("CargoBayOpen")));
	}
	if (CurrentScale.X >= BossCaptureScale.X)
	{
		this->Tags.AddUnique(FName(TEXT("BossOpen")));
	}

	Eating = false;
	float CurrentMaxRange = this->MeleeWeapon->GetMaxRange();
	CurrentMaxRange *= ScalingEating;
	this->MeleeWeapon->SetMaxRange(CurrentMaxRange);

	float CurrentDamage = this->MeleeWeapon->GetDamage();
	CurrentDamage *= ScalingEating;
	this->MeleeWeapon->SetDamage(CurrentDamage);

	float CurrentWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	CurrentWalkSpeed *= ScalingEating;
	GetCharacterMovement()->MaxWalkSpeed = CurrentWalkSpeed;

	MaxHealth *= ScalingEating;

}

bool ABerserkerCharacter::IsEating() const
{
	return Eating;
}

bool ABerserkerCharacter::IsTrueDead() const
{
	return TrueDeath;
}

bool ABerserkerCharacter::SetTrueDead(bool TrueDeathValue)
{
	TrueDeath = TrueDeathValue;
	return TrueDeath;
}

void ABerserkerCharacter::PlayResurrection()
{
	UE_LOG(LogTemp, Error, TEXT("Berserk Resurrection"));	
	Health = MaxHealth;
	IsDead();	
}

void ABerserkerCharacter::SwingWeapon()
{
	Super::SwingWeapon();
	if (AttackSound)
	{
		UGameplayStatics::SpawnSoundAttached(AttackSound, GetMesh(), TEXT("Status"));
	}

}

