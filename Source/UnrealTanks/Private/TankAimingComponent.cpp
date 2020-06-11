// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

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
		auto AimDirection = Velocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
	} 
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	if ( !ensure(Barrel) || !ensure(Turret) ) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}

void UTankAimingComponent::Fire() {

		bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
		if (ensure(Barrel) && ensure(ProjectileBlueprint) && isReloaded) {
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
			);

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}

}

