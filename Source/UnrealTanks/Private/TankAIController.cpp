// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp,Warning,TEXT("TankAIController started"));
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());

    if ( PlayerTank ) {

        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        ControlledTank->Fire();
    }

}
