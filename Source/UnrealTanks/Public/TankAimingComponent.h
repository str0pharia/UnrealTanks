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
	Locked
};

class UTankBarrel;	
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALTANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	


	void AimAt(FVector HitLocation);

	void MoveBarrelTowards(FVector AimDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Initialise(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 10000.f;

private:

	bool bWantsBeginPlay = true;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;


};
