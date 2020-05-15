// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesInventoryInterface.generated.h"


/**
 * 
 */
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UCesInventoryInterface : public UInterface
{
    GENERATED_BODY()
};


class EQUIPMENTSYSTEM_API ICesInventoryInterface
{
    GENERATED_BODY()

    
public:
    bool AddItemToSlot(FCesItemData ItemData, int32 Slot);
   
};
