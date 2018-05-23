// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>
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
  bool hasPhysicsHandleComponent();
  bool hasInputComponent();
  void configureInputComponent();
  void grabObject();
  void releaseObject();

private:
  UPROPERTY(EditAnywhere)
  float player_grabbing_reach_ = 50.f;

  UPhysicsHandleComponent* physics_handle_;
  UInputComponent* input_component_;
};
