// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "CesItemSlotWidget.h"
#include "EquipmentSystem.h"
#include "Blueprint/DragDropOperation.h"
#include "CesDragDropItem.generated.h"



UCLASS()
class EQUIPMENTSYSTEM_API UCesDragDropItem : public UDragDropOperation
{
    GENERATED_BODY()

public:
    UPROPERTY();
    FCesItemData ItemData;

    UPROPERTY();
    class UCesInventoryComponent* FromInventoryComponent;

    UPROPERTY();
    int32 FromSlotIndex;

    UPROPERTY();
    UCesItemSlotWidget* FromSlotWidget;
};
