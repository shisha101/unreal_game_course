// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
  // features off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
  Super::BeginPlay();
  checkTriggerVolumeComponent();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  TriggerVolumeOpenDoor();
  delayedClose();
}

bool UOpenDoor::TriggerVolumeOpenDoor()
{
  if (!pressure_plate_) return false;

  TArray<AActor*> actors_overlapping_pressure_plate;
  pressure_plate_->GetOverlappingActors(actors_overlapping_pressure_plate);

  auto total_wegiht_on_trigger_volume = 0.f;
  for (const auto& actor : actors_overlapping_pressure_plate)
  {
    total_wegiht_on_trigger_volume += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
  }

  if (total_wegiht_on_trigger_volume < pressure_plate_trigger_weight_) return false;

  openDoor();
  return true;
}

void UOpenDoor::openDoor()
{
  door_open_time_ = GetWorld()->GetTimeSeconds();
  open_door_request_.Broadcast();
}

void UOpenDoor::closeDoor()
{
  close_door_request_.Broadcast();
  GetOwner()->SetActorRotation(FRotator(0.f, -90.0f, 0.f));
}

void UOpenDoor::delayedClose()
{
  const auto current_time = GetWorld()->GetTimeSeconds();
  if (current_time - door_open_time_ >= delay_to_door_close_) closeDoor();
}

bool UOpenDoor::checkTriggerVolumeComponent()
{
  if (pressure_plate_) return true;
  UE_LOG(LogTemp, Error, TEXT("Object %s could not find TriggerVolume component."), *GetOwner()->GetName());
  return false;
}
