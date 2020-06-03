// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class UNREALTANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable,Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable,Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

protected:

	UTankAimingComponent* TankAimingComponent = nullptr;

private:

	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;

};
