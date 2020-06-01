// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());     


}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp,Warning,TEXT("TankPlayerController started"));
}


void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair() 
{

    if (!GetControlledTank()) { return; }
    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
        GetControlledTank()->AimAt(HitLocation);
    }

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    int32 ViewportSizeX,ViewportSizeY;

    GetViewportSize(ViewportSizeX,ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    FVector LookDirection;
    if ( GetLookDirection(ScreenLocation,LookDirection)) 
    {
        //UE_LOG(LogTemp,Warning,TEXT("Look Direction = %s"),*LookDirection.ToString());
        if ( GetLookVectorHitLocation(LookDirection,HitLocation) ) {

            UE_LOG(LogTemp,Warning,TEXT("Hit Location = %s"),*HitLocation.ToString())
        }
    }

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if ( GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility) 
        ) 
    {

        HitLocation = HitResult.Location;
        return true;

    }

    HitLocation = FVector(0);
    return false;
}