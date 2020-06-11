// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


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

        MoveToActor(PlayerTank, 3000);

        AimingComponent->AimAt(PlayerTank->GetActorLocation());

        //ControlledTank->Fire();
    }

}
