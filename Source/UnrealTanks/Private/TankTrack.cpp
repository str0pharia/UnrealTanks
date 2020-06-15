// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "math.h"


void UTankTrack::BeginPlay() {
      Super::BeginPlay();
      OnComponentHit.AddDynamic(this,&UTankTrack::OnHit);

}

void UTankTrack::SetThrottle(float throttle) {
      
      CurrentThrottle = FMath::Clamp(CurrentThrottle + throttle,-1.0f,1.0f);

}

void UTankTrack::DriveTrack() {
      
      auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
      auto ForceLocation = GetComponentLocation();
      auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
      TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);


}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

      DriveTrack();
      ApplyCorrectionForce();
      CurrentThrottle = 0;
}



void UTankTrack::ApplyCorrectionForce() {
           
      auto SlippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());

      auto CorrectionAcceleration = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

      auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

      auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

      TankRoot->AddForce(CorrectionForce);
}