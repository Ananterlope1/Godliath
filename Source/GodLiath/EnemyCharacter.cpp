// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "MeleeWeapon.h"
#include "Components/CapsuleComponent.h"
#include "GodLiathGameModeBase.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;	

	if (MeleeClass)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(MeleeClass);

		MeleeWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("MeleeWeapon_R"));
		MeleeWeapon->SetOwner(this);
	}
	
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AEnemyCharacter::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AEnemyCharacter::MoveRight);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &AEnemyCharacter::LookUpRate);
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &AEnemyCharacter::LookRightRate);
	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AEnemyCharacter::SwingWeapon);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	

	UE_LOG(LogTemp, Warning, TEXT("Enemy damage taken: %f"), DamageToApply);
	UE_LOG(LogTemp, Warning, TEXT("Enemy Health: %f"), Health);
	
	
	return DamageToApply;

}

void AEnemyCharacter::SwingWeapon()
{
	MeleeWeapon->SwingWeapon();

}

// Can't use as UFUNCTION isn't overrideable in child
// bool AEnemyCharacter::IsDead() 
// {	
// 	return Health <= 0;
// }

void AEnemyCharacter::MoveForward(float AxisValue) 
{

	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AEnemyCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AEnemyCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AEnemyCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

bool AEnemyCharacter::IsEatable()
{
	// if (Eatable)
	// {
	// 	this->Tags.Add(FName("Eatable"));
	// }
	
	return Eatable;
}

bool AEnemyCharacter::SetIsEatable(bool SetIsEatable)
{
	Eatable = SetIsEatable;
	return Eatable;
}

UParticleSystem* AEnemyCharacter::GetEatenEmitter()
{
	return EatenEmitter;
}
