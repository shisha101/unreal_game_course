// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
    Super::BeginPlay();
    const auto object_location = GetOwner()->GetActorLocation();
    const auto rotation_euler_deg = GetOwner()->GetActorRotation().Euler();

    UE_LOG(LogTemp,Warning,TEXT("%s is in the BeginPlay function Postion: x=%f, y=%f, z=%f. Rotation (Euler): r=%f, p=%f, y=%f ."),
           *GetOwner()->GetHumanReadableName(),
           object_location.X, object_location.Y, object_location.Z,
           rotation_euler_deg.X, rotation_euler_deg.Y, rotation_euler_deg.Z);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

