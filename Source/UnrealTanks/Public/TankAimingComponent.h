// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;	
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALTANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTankAimingComponent();

	UFUNCTION(BlueprintCallable)
	void Initialise(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	int GetRoundsLeft() const;

	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 10000.f;


	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	int RoundsLeft = 3;
private:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ReloadTimeSeconds = 3.f;

	double LastFireTime = 0;

	FVector _AimDirection;


};
