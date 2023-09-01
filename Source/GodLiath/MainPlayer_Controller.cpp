// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer_Controller.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void AMainPlayer_Controller::BeginPlay()
{
    Super::BeginPlay();
    HUD = CreateWidget(this, HUDClass);
    HUD->AddToViewport();
}

void AMainPlayer_Controller::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    HUD->RemoveFromParent();
    if (bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
            FTimerHandle Handle;
	        FTimerDelegate Delegate;
	        Delegate.BindUFunction( this, FName("ReturnToMain"));
            GetWorldTimerManager().SetTimer(Handle, Delegate, RestartDelay, false);
        }
    }else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

        if (LoseScreen != nullptr)
        {            
            LoseScreen->AddToViewport();
            GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

        }
    }

    // GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

UUserWidget* AMainPlayer_Controller::GetPlayerHUD()
{
    return HUD;
}

bool AMainPlayer_Controller::ReturnToMain() const
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/MenuLevel"), TRAVEL_Absolute);
    return true;
}


