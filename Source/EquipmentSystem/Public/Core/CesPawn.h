// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesPawn.generated.h"


class USpineSkeletonRendererComponent;
class USpineSkeletonAnimationComponent;


UCLASS()
class EQUIPMENTSYSTEM_API ACesPawn : public APawn
{
    GENERATED_BODY()

public:
    ACesPawn();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    USpineSkeletonRendererComponent* SkeletonRendererComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    USpineSkeletonAnimationComponent* SkeletonAnimationComponent;

protected:
    void BeginPlay() override;
};
