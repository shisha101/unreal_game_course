// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MY_ESCAPE_GAME_API UOpenDoor : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UOpenDoor();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                             FActorComponentTickFunction* ThisTickFunction) override;

private:
  bool TriggerVolumeOpenDoor();
  bool openDoor();
  bool closeDoor();
  void delayedClose();
  bool checkTriggerVolumeComponent();

private:
  UPROPERTY(EditAnywhere)
  ATriggerVolume* pressure_plate_ = nullptr;

  UPROPERTY(EditAnywhere)
  float door_open_angle_ = 160.f;

  UPROPERTY(EditAnywhere)
  float delay_to_door_close_ = 0.2f;

  UPROPERTY(EditAnywhere)
  float pressure_plate_trigger_weight_ = 9.f;  // [kg]

  float door_open_time_;
};
