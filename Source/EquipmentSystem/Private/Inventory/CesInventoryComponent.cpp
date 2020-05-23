// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "Inventory/CesInventoryComponent.h"
#include "CesTypes.h"
#include "Items/CesItem.h"


void UCesInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    for (int i = 0; i < InitialSlotCount; ++i)
    {
        Items.Emplace(FCesItemData(nullptr, 0));
    }

    SlotCount += InitialSlotCount;
}


bool UCesInventoryComponent::IsValidSlot(const int32 SlotIndex) const
{
    if (Items.IsValidIndex(SlotIndex))
    {
        return true;
    }

    UE_LOG(CesLog, Error, TEXT("UCesInventoryComponent::IsValidSlot - Slot Index is invalid."))
    return false;
}


bool UCesInventoryComponent::AddItem(FCesItemData ItemData)
{
    bool bItemWasAdded = false;

    for (int i = 0; i < SlotCount; ++i)
    {
        bItemWasAdded = AddItemToSlot(ItemData, i);

        if (bItemWasAdded) { break; }
    }

    return bItemWasAdded;
}

bool UCesInventoryComponent::AddItemToSlot(FCesItemData ItemData, int32 SlotIndex)
{
    bool bItemWasAdded = false;

    if (!IsValidSlot(SlotIndex)) return false;

    // Increase item count if item is already in that slot and they are stackable
    if (Items[SlotIndex].Item == ItemData.Item && Items[SlotIndex].Item->IsStackable)
    {
        Items[SlotIndex].Quantity += ItemData.Quantity;
        bItemWasAdded = true;
    }

    // Add item to empty slot
    if (Items[SlotIndex].Quantity == 0)
    {
        Items[SlotIndex] = ItemData;
        bItemWasAdded = true;
    }

    if (bItemWasAdded && OnInventoryItemAdded.IsBound())
    {
        OnInventoryItemAdded.Broadcast(SlotIndex, Items[SlotIndex]);
    }

    return bItemWasAdded;
}


bool UCesInventoryComponent::EmptySlot(int32 SlotIndex)
{
    if (!IsValidSlot(SlotIndex)) return false;

    FCesItemData RemovedItem = Items[SlotIndex];
    
    Items[SlotIndex].Item = nullptr;
    Items[SlotIndex].Quantity = 0;

    if (OnInventoryItemRemoved.IsBound())
    {
        OnInventoryItemRemoved.Broadcast(SlotIndex, RemovedItem);
    }

    return true;
}


bool UCesInventoryComponent::IsSlotFilled(int32 SlotIndex)
{
    if (!IsValidSlot(SlotIndex)) return false;

    if (Items[SlotIndex].IsValid())
    {
        return true;
    }

    return false;
}
