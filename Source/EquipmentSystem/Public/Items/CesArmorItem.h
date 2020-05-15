// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesAssetManager.h"
#include "Items/CesEquipableItem.h"
#include "CesArmorItem.generated.h"

/**
 * Base class for a Armor Item Data Asset
 */
UCLASS()
class EQUIPMENTSYSTEM_API UCesArmorItem : public UCesEquipableItem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    EArmorItemType ArmorType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Consumable)
    TSubclassOf<AActor> ArmorActor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
    float BaseArmor;
};
