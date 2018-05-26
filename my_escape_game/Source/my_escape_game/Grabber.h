// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MY_ESCAPE_GAME_API UGrabber : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UGrabber();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                             FActorComponentTickFunction* ThisTickFunction) override;

private:
  bool componentsValid();
  void configureInputComponent();
  bool hasInputComponent();
  bool hasPhysicsHandleComponent();
  void grabObject();
  void releaseObject();
  FVector getGrabReachLocationInWorld();
  FHitResult getPhysicsObjectInReach();

private:
  UPhysicsHandleComponent* physics_handle_{ nullptr };
  UInputComponent* input_component_{ nullptr };

  UPROPERTY(EditAnywhere)
  float player_grabbing_reach_ = 100.f;
};
