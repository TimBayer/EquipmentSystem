// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesAssetManager.h"
#include "Items/CesItem.h"
#include "CesConsumableItem.generated.h"

/**
 * Base class for a Consumable Item Data Assets
 */
UCLASS()
class EQUIPMENTSYSTEM_API UCesConsumableItem : public UCesItem
{
    GENERATED_BODY()

public:
    UCesConsumableItem();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Consumable)
    EConsumableType ConsumableType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Consumable)
    int32 MaxStackSize;
};
