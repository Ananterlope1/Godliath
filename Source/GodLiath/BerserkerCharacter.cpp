// Fill out your copyright notice in the Description page of Project Settings.


#include "BerserkerCharacter.h"

#include "MeleeWeapon.h"
#include "Components/CapsuleComponent.h"

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

	MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(MeleeClass);

	MeleeWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("MeleeWeapon_R"));
	MeleeWeapon->SetOwner(this);
	
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

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ABerserkerCharacter::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &ABerserkerCharacter::MoveRight);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &ABerserkerCharacter::LookUpRate);
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &ABerserkerCharacter::LookRightRate);
	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ABerserkerCharacter::SwingWeapon);

}

float ABerserkerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health Left: %f"), Health);

	if (IsDead())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// Wait
		// Heal back Health to full
		// Health = MaxHealth;
		// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	

	return DamageToApply;

}

void ABerserkerCharacter::SwingWeapon()
{
	MeleeWeapon->SwingWeapon();

}

bool ABerserkerCharacter::IsDead() 
{	
	return Health <= 0;
}

void ABerserkerCharacter::MoveForward(float AxisValue) 
{

	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ABerserkerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ABerserkerCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ABerserkerCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}
