// Fill out your copyright notice in the Description page of Project Settings.


#include "Narration_Trigger.h"
#include "BerserkerCharacter.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.h"

// Sets default values
ANarration_Trigger::ANarration_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Narration_Box"));
	// SetRootComponent(HitBox);
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ANarration_Trigger::OnOverlapBegin);
	// HitBox->OnComponentHit.AddDynamic(this, &ANarration_Trigger::OnHit);
	

}

// Called when the game starts or when spawned
void ANarration_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	
}

// Called every frame
void ANarration_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANarration_Trigger::OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	UE_LOG(LogTemp, Display, TEXT("Test"));
	if(NarrationTag!="Normal")
	{

		if(OtherActor->IsA<ABerserkerCharacter>() && OtherActor->ActorHasTag(NarrationTag))
		{
			if(IsValid(WidgetTextClass))
			{
				UUserWidget* TextWidget = CreateWidget(GetWorld(), WidgetTextClass);
				if(TextWidget != nullptr)
				{
					TextWidget->AddToViewport();
					NarrationDelegate.BindUFunction( this, FName("CleanUpNarration"), TextWidget);
					GetWorldTimerManager().SetTimer(NarrationHandle, NarrationDelegate, NarrationTimer, false);	
					
				}
			}
		}
	}else if (OtherActor->IsA<APlayerCharacter>())
	{
		UE_LOG(LogTemp, Display, TEXT("Not tag and player overlap"));
		if(IsValid(WidgetTextClass))
			{
				UUserWidget* TextWidget = CreateWidget(GetWorld(), WidgetTextClass);
				if(TextWidget != nullptr)
				{
					TextWidget->AddToViewport();					
					
					NarrationDelegate.BindUFunction( this, FName("CleanUpNarration"), TextWidget);
					GetWorldTimerManager().SetTimer(NarrationHandle, NarrationDelegate, NarrationTimer, false);	
					
				}
			}
	}

}

void ANarration_Trigger::CleanUpNarration(UUserWidget* TextWidget)
{
	if (TextWidget != nullptr)
	{
		// TextWidget->BeginDestroy();

		TextWidget->RemoveFromParent();

	}
	
	
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

