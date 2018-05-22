// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
  // features off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
  Super::BeginPlay();

  UE_LOG(LogTemp, Warning, TEXT("grabber component active"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  FVector view_location;
  FRotator view_orientation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(view_location, view_orientation);
  const auto ray_end_point = view_location + view_orientation.Vector() * player_grabbing_reach_;
  //    GetOwner()->GetActorEyesViewPoint(view_location,view_orientation);

  DrawDebugLine(GetWorld(), view_location, ray_end_point, FColor(255, 0, 0), false, -1.f, 0, 1);

  FHitResult object_hit;
  const FCollisionQueryParams collision_query_params(FName(""), false, GetOwner());
  if (GetWorld()->LineTraceSingleByObjectType(object_hit, view_location, ray_end_point,
                                              FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                              FCollisionQueryParams(FName(""), false, GetOwner())))
    UE_LOG(LogTemp, Warning, TEXT("can grab %s"), *object_hit.GetActor()->GetName());
}
