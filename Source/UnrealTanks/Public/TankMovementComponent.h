// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALTANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


private:

	UTankTrack* LeftTrack;
	UTankTrack* RightTrack;


public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendRotate(float Throw);

	UFUNCTION(BlueprintCallable)
	void Initialise(UTankTrack* LeftTankTrack, UTankTrack* RightTankTrack);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
