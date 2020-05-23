// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesAssetManager.h"
#include "Items/CesEquipableItem.h"
#include "CesWeaponItem.generated.h"

/**
 * Base class for a Weapon Item Data Asset
 */
UCLASS()
class EQUIPMENTSYSTEM_API UCesWeaponItem : public UCesEquipableItem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
    EWeaponItemType WeaponType;
};
