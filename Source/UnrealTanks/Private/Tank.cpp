// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()     
{                  
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Moving Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::Fire() {
/*
		bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
		if (ensure(TankAimingComponent) && ensure(Barrel) && ensure(ProjectileBlueprint) && isReloaded) {
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
			);

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
*/
}

