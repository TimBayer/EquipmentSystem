// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesPlayerController.generated.h"


class UCesInventoryContainerComponent;


UCLASS()
class EQUIPMENTSYSTEM_API ACesPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ACesPlayerController();


protected:
    virtual void BeginPlay() override;
};
