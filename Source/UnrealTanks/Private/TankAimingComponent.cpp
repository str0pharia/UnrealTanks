// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Called when the game starts

UTankAimingComponent::UTankAimingComponent() {

	PrimaryComponentTick.bCanEverTick = true;	
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{

	if ( RoundsLeft <= 0 ) {
		FiringState = EFiringState::OutOfAmmo;
	} else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds) {

		FiringState = EFiringState::Reloading;

	} else if (IsBarrelMoving()) {

		FiringState = EFiringState::Aiming;
		
	} else {

		FiringState = EFiringState::Locked;
	}

}

bool UTankAimingComponent::IsBarrelMoving() {

	if (!ensure(Barrel)) {return false;}

	return !Barrel->GetForwardVector().Equals(_AimDirection);
}

void UTankAimingComponent::Initialise(UTankBarrel* TankBarrel, UTankTurret* TankTurret) {
    if ( !ensure(TankBarrel) || !ensure(TankTurret) ) {return;}
	Barrel = TankBarrel;
	Turret = TankTurret;
}

void UTankAimingComponent::AimAt(FVector HitLocation) 
{

	if ( !ensure(Barrel) || !ensure(Turret) ) { return; }


	FVector Velocity(0);


	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		Velocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if ( bHaveAimSolution )
	{
		_AimDirection = Velocity.GetSafeNormal();

		MoveBarrelTowards(_AimDirection);
	} 
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	if ( !ensure(Barrel) || !ensure(Turret) ) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	/* if Yaw  > 180 (degrees), rotate in opposite direction */
	if ( FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	} else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	

}


EFiringState UTankAimingComponent::GetFiringState() const {

	return FiringState;

}

int UTankAimingComponent::GetRoundsLeft() const {

	return RoundsLeft;

}

void UTankAimingComponent::Fire() {

		if ( FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {
			if (ensure(Barrel) && ensure(ProjectileBlueprint)) {
				auto Projectile = GetWorld()->SpawnActor<AProjectile>(
					ProjectileBlueprint,
					Barrel->GetSocketLocation(FName("Projectile")),
					Barrel->GetSocketRotation(FName("Projectile"))
				);

				Projectile->LaunchProjectile(LaunchSpeed);
				LastFireTime = FPlatformTime::Seconds();
				RoundsLeft--;
			}
		}

}

