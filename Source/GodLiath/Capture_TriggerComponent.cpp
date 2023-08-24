// Fill out your copyright notice in the Description page of Project Settings.


#include "Capture_TriggerComponent.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"


UCapture_TriggerComponent::UCapture_TriggerComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    // this->OnComponentBeginOverlap.AddDynamic(this, &UCapture_TriggerComponent::OnOverlapBegin);
    // OnComponentEndOverlap.AddDynamic(this, &UCapture_TriggerComponent::OnOverlapEnd);
    
}

void UCapture_TriggerComponent::BeginPlay()
{
    Super::BeginPlay();

}

void UCapture_TriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// void OnOverlapBegin(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
// {

// }

// void OnOverlapEnd(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {

// }