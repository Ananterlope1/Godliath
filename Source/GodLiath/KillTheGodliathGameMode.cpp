// Fill out your copyright notice in the Description page of Project Settings.


#include "KillTheGodliathGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "BerserkAIController.h"

void AKillTheGodliathGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("Pawn Was killed"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }
    
    //For check over the BerserkerAI. Might be more in later levels so for loop.
    for (ABerserkAIController* Controller : TActorRange<ABerserkAIController>(GetWorld()))
    {
        if (!Controller->IsTrueDead())
        {
            //Early return as game not over yet
            return;
        }
    }
    
    EndGame(true);

}

void AKillTheGodliathGameMode::EndGame(bool bIsPlayerWinner)
{
    // Goes over all controllers in the world/ level and returns them as a list
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool IsPlayerController = Controller->IsPlayerController();
        if (bIsPlayerWinner)
        {
            Controller->GameHasEnded(Controller->GetPawn(), IsPlayerController);
        }else 
        {
            Controller->GameHasEnded(Controller->GetPawn(), !IsPlayerController);
        }
        
         
    }
}
