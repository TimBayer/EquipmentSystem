// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesAssetManager.h"
#include "Items/CesEquipableItem.h"
#include "CesAccessoryItem.generated.h"

/**
 * Base class for a Accessory Item Data Asset
 */
UCLASS()
class EQUIPMENTSYSTEM_API UCesAccessoryItem : public UCesEquipableItem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    EAccessoryItemType AccessoryType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Consumable)
    TSubclassOf<AActor> AccessoryActor;
};
