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

  UE_LOG(LogTemp, Warning, TEXT("grabber component init"));

  if (componentsValid())
    configureInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  FVector view_location;
  FRotator view_orientation;
  //  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(view_location, view_orientation);
  GetOwner()->GetActorEyesViewPoint(view_location, view_orientation);
  const auto ray_end_point = view_location + view_orientation.Vector() * player_grabbing_reach_;

  DrawDebugLine(GetWorld(), view_location, ray_end_point, FColor(255, 0, 0), false, -1.f, 0, 1);

  FHitResult object_hit;
  const FCollisionQueryParams collision_query_params(FName(""), false, GetOwner());
  if (GetWorld()->LineTraceSingleByObjectType(object_hit, view_location, ray_end_point,
                                              FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                              FCollisionQueryParams(FName(""), false, GetOwner())))
    UE_LOG(LogTemp, Warning, TEXT("can grab %s"), *object_hit.GetActor()->GetName());
}

bool UGrabber::componentsValid()
{
  return hasPhysicsHandleComponent() && hasInputComponent();
}

bool UGrabber::hasPhysicsHandleComponent()
{
  physics_handle_ = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if (physics_handle_ != nullptr)
    return true;
  UE_LOG(LogTemp, Error, TEXT("Object %s could not find PhysicsHandler component."), *GetOwner()->GetName());
  return false;
}

bool UGrabber::hasInputComponent()
{
  input_component_ = GetOwner()->FindComponentByClass<UInputComponent>();
  if (input_component_ != nullptr)
    return true;
  UE_LOG(LogTemp, Error, TEXT("Object %s could not find Input component."), *GetOwner()->GetName());
  return false;
}

void UGrabber::configureInputComponent()
{
  input_component_->BindAction("GrabObject", EInputEvent::IE_Pressed, this, &UGrabber::grabObject);
  input_component_->BindAction("ReleaseObject", EInputEvent::IE_Released, this, &UGrabber::releaseObject);
}

void UGrabber::grabObject()
{
  UE_LOG(LogTemp, Warning, TEXT("attempting to grab object"))
}

void UGrabber::releaseObject()
{
  UE_LOG(LogTemp, Warning, TEXT("attempting to release object"))
}
