// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h" 
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) 
{
	//auto TankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp,Warning,TEXT("%s aiming at %s"),*TankName,*HitLocation.ToString());

	if (!Barrel) { return; }


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
		//auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp,Warning,TEXT("%s is aiming at %s"),*TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {

	Barrel = BarrelToSet;
}

