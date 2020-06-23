// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp,Warning,TEXT("TankAIController started"));
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if ( ensure(PlayerTank) && ensure(ControlledTank) ) {
	    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	    if (!ensure(AimingComponent)){return;}

        MoveToActor(PlayerTank, AcceptanceRadius);

        AimingComponent->AimAt(PlayerTank->GetActorLocation());

        /* Fire if firing state = Locked */
        if ( AimingComponent->GetFiringState() == EFiringState::Locked ) {
            AimingComponent->Fire();
        }
        
    }

}

void ATankAIController::SetPawn(APawn* InPawn) 
{
    Super::SetPawn(InPawn);
    
    if (InPawn) {
        auto TankPawn = Cast<ATank>(InPawn);

        if (!ensure(TankPawn) ) { return; }

        TankPawn->OnDeath.AddUniqueDynamic(this,&ATankAIController::OnTankDestroyed);
    }
}


void ATankAIController::OnTankDestroyed() 
{

    UE_LOG(LogTemp,Warning,TEXT("Tank Destroyed"));
}
