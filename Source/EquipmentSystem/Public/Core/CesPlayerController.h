// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesPlayerController.generated.h"


class UCesInventoryComponent;


/**
 * 
 */
UCLASS()
class EQUIPMENTSYSTEM_API ACesPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ACesPlayerController();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    UCesInventoryComponent* InventoryComponent;

protected:
    virtual void BeginPlay() override;
};
