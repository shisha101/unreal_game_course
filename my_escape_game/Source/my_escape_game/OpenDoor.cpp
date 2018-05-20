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
}

bool UOpenDoor::TriggerVolumeOpenDoor()
{
    if (!pressure_plate_) return false;
    if(pressure_plate_->IsOverlappingActor(GetWorld()->GetFirstPlayerController()->GetPawn())) return openDoor();
    return false;
}

bool UOpenDoor::openDoor()
{
    return GetOwner()->SetActorRotation(FRotator(0.f, -120.f, 0.f));
}

