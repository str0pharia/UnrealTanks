// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALTANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000;

private:

	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	void DriveTrack();

	void ApplyCorrectionForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
};
