// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTankTrack, UTankTrack* RightTankTrack) {
    if ( !LeftTankTrack || !RightTankTrack ) {return;}
    LeftTrack = LeftTankTrack;
    RightTrack = RightTankTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotate(float Throw) {

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {

    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward,AIForwardIntention);   
    IntendMoveForward(ForwardThrow);

    auto RotationThrow = FVector::CrossProduct(TankForward,AIForwardIntention).Z;   
    IntendRotate(RotationThrow);

}