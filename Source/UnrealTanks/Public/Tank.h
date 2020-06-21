// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class UNREALTANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:

	ATank();

	int32 StartingHealth = 100;
	int32 Health = StartingHealth;

public:

	int32 GetHealth();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

};
