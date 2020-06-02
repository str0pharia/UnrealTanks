// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());     
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if ( !PlayerPawn ) { return nullptr; }
    return Cast<ATank>(PlayerPawn);     

}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp,Warning,TEXT("TankAIController started"));
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if ( GetPlayerTank() ) 
    {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}
