// Fill out your copyright notice in the Description page of Project Settings.


#include "KillTheGodliathGameMode.h"


void AKillTheGodliathGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("Pawn Was killed"));
}
