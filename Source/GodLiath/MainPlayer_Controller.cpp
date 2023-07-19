// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer_Controller.h"
#include "TimerManager.h"


void AMainPlayer_Controller::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UE_LOG(LogTemp, Warning, TEXT("You Have Died!"));

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
