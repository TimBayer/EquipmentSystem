// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesAssetManager.h"
#include "Items/CesItem.h"
#include "CesEquipableItem.generated.h"

/**
* Base class for a Equipable Item Data Assets
*/
UCLASS()
class EQUIPMENTSYSTEM_API UCesEquipableItem : public UCesItem
{
    GENERATED_BODY()

public:
     UCesEquipableItem();
};
