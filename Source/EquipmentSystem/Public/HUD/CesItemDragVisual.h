// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "Blueprint/UserWidget.h"
#include "CesItemDragVisual.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class EQUIPMENTSYSTEM_API UCesItemDragVisual : public UUserWidget
{
    GENERATED_BODY()

    
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta=( ExposeOnSpawn="true", DisplayName="Item Data" ))
    FCesItemData ItemData;
};
