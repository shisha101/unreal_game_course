// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
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
    if(pressure_plate_->IsOverlappingActor(GetWorld()->GetFirstPlayerController()->GetPawn())) return openDoor();
    return false;
}

bool UOpenDoor::openDoor()
{
    door_open_time_ = GetWorld()->GetTimeSeconds();
    return GetOwner()->SetActorRotation(FRotator(0.f, door_open_angle_, 0.f));
}

bool UOpenDoor::closeDoor()
{
    return GetOwner()->SetActorRotation(FRotator(0.f, -90.0f, 0.f));
}

void UOpenDoor::delayedClose()
{
    const auto current_time = GetWorld()->GetTimeSeconds();
    if (current_time - door_open_time_ >= delay_to_door_close_) closeDoor();
}
