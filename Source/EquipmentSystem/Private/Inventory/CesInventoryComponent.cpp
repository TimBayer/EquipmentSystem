// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "Inventory/CesInventoryComponent.h"
#include "CesTypes.h"
#include "Items/CesItem.h"


UCesInventoryComponent::UCesInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    SlotCount = 30;

    for (int i = 0; i < SlotCount; ++i)
    {
        SlottedItems.Add(i);
    }
}


void UCesInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}


bool UCesInventoryComponent::AddItem(FCesItemData ItemData)
{
    bool bItemWasAdded = false;

    // increase item count
    for (auto& Elem : SlottedItems)
    {
        if (Elem.Value.Item == ItemData.Item)
        {
            Elem.Value.Quantity += ItemData.Quantity;
            bItemWasAdded = true;
            break;
        }
    }

    // Add item to first empty slot
    if (!bItemWasAdded)
    {
        for (auto& Elem : SlottedItems)
        {
            if (Elem.Value.Quantity == 0)
            {
                Elem.Value = ItemData;
                bItemWasAdded = true;
                break;
            }
        }
    }

    if (bItemWasAdded && OnInventoryChanged.IsBound())
    {
        OnInventoryChanged.Broadcast();
    }

    return bItemWasAdded;
}


bool UCesInventoryComponent::AddItemToSlot(FCesItemData ItemData, int32 Slot)
{
    bool bItemWasAdded = false;

    if (!SlottedItems.Contains(Slot))
    {
        return false;
    }

    // Increase item count if item is already in that slot
    if (SlottedItems[Slot].Item == ItemData.Item)
    {
        SlottedItems[Slot].Quantity += ItemData.Quantity;
        bItemWasAdded = true;
    }

    if (SlottedItems[Slot].Quantity == 0)
    {
        SlottedItems[Slot] = ItemData;
        bItemWasAdded = true;
    }

    if (bItemWasAdded && OnInventoryChanged.IsBound())
    {
        OnInventoryChanged.Broadcast();
    }

    return bItemWasAdded;
}


void UCesInventoryComponent::EmptySlot(int32 Slot)
{
    SlottedItems[Slot] = FCesItemData();
}
