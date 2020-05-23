// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "HUD/CesItemSlotWidget.h"
#include "Components/Image.h"
#include "HUD/CesDragDropItem.h"
#include "HUD/CesItemDragVisual.h"
#include "Items/CesItem.h"


void UCesItemSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!InventoryComponent)
    {
        UE_LOG(CesLog, Log, TEXT( "UCesItemSlotWidget::NativeConstruct: SlotWidget currently not assoiciated with any InventoryComponent!" ))
    }

    SetInventoryComponent(InventoryComponent);
}


void UCesItemSlotWidget::SetInventoryComponent(UCesInventoryComponent* NewInventoryComponent)
{
    if (NewInventoryComponent)
    {
        InventoryComponent = NewInventoryComponent;

        // Item Events
        InventoryComponent->OnInventoryItemAdded.AddDynamic(this, &UCesItemSlotWidget::OnItemAddedNative);
        InventoryComponent->OnInventoryItemRemoved.AddDynamic(this, &UCesItemSlotWidget::OnItemRemovedNative);
    }
}


void UCesItemSlotWidget::OnItemAddedNative(int32 AddedItemSlotIndex, FCesItemData AddedItem)
{
    if (AddedItemSlotIndex == SlotIndex)
    {
        ItemData = AddedItem;
        OnItemAdded(AddedItem);
    }
}


void UCesItemSlotWidget::OnItemRemovedNative(int32 RemovedSlotIndex, FCesItemData RemovedItem)
{
    if (RemovedSlotIndex == SlotIndex)
    {
        ItemData = FCesItemData();
        OnItemRemoved();
    }
}


FReply UCesItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }
    return Reply;
}


void UCesItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                              UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    // Set input to UI only on drag so we don't affect game
    GetOwningPlayer()->SetInputMode(FInputModeUIOnly());

    OutOperation = CreateItemDrag();
}


UDragDropOperation* UCesItemSlotWidget::CreateItemDrag()
{
    // Create object that will carry our item data to the new slot widget
    UCesDragDropItem* DragDropOperation = NewObject<UCesDragDropItem>();

    if (ItemData.IsValid() && InventoryComponent)
    {
        if (ItemDragVisualClass)
        {
            // Add data required for drop operation
            DragDropOperation->ItemData = ItemData;
            DragDropOperation->FromInventoryComponent = InventoryComponent;
            DragDropOperation->FromSlotIndex = SlotIndex;
            DragDropOperation->FromSlotWidget = this;

            // Create and populate the widget we see while dragging
            UCesItemDragVisual* DragVisual = CreateWidget<UCesItemDragVisual>(GetOwningPlayer(), ItemDragVisualClass);
            DragVisual->ItemData = ItemData;
            DragDropOperation->DefaultDragVisual = DragVisual;

            DragDropOperation->Pivot = EDragPivot::MouseDown;
        }
        else
        {
            UE_LOG(CesLog, Error, TEXT("UCesItemSlotWidget::CreateItemDrag - ItemDragVisualClass must be set on item slot."))
        }
    }

    return DragDropOperation;
}


void UCesItemSlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

    // Set input mode back
    GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
}


bool UCesItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                      UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    // Set input mode back
    GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());

    if (!InventoryComponent)
    {
        UE_LOG(CesLog, Error, TEXT("UCesItemSlotWidget::NativeOnDrop - InventoryComponent not found for this slot!"))
        return false;
    }

    UCesDragDropItem* DropOperation = Cast<UCesDragDropItem>(InOperation);
    if (DropOperation && DropOperation->ItemData.IsValid())
    {
        // If we are dropping onto the same slot, do nothing
        if (DropOperation->FromSlotWidget == this)
        {
            return false;
        }

        // If the item is compatible with the slot type, allow the drop to take place
        if (SlotAllowance == EInvSlotAllowance::AllItems || DropOperation->ItemData.Item->SlotAllowance == SlotAllowance)
        {
            // Attempt to add item to current slot
            const bool bItemAdded = InventoryComponent->AddItemToSlot(DropOperation->ItemData, SlotIndex);

            if (bItemAdded)
            {
                // Remove item from previous Inventory slot
                DropOperation->FromInventoryComponent->EmptySlot(DropOperation->FromSlotIndex);
                return true;
            }

            // If there is a valid item in this slot and swap slot is valid for this slots current item
            // then attempt to swap items
            if (ItemData.IsValid() &&
                (DropOperation->FromSlotWidget->SlotAllowance == EInvSlotAllowance::AllItems ||
                    DropOperation->FromSlotWidget->SlotAllowance == ItemData.Item->SlotAllowance))
            {
                //UE_LOG(CesLog, Warning, TEXT( "current target: %s"), *ItemData.Item->ItemName.ToString())
                //UE_LOG(CesLog, Warning, TEXT( "Swap target: %s"), *DropOperation->ItemData.Item->ItemName.ToString())

                // Store current item
                FCesItemData CurrentItemData = ItemData; // InventoryComponent->Items[SlotIndex];

                // Clear slots so they accept the new items
                InventoryComponent->EmptySlot(SlotIndex);
                DropOperation->FromInventoryComponent->EmptySlot(DropOperation->FromSlotIndex);

                //Swap items
                bool bDidSwapTarget = DropOperation->FromInventoryComponent->AddItemToSlot(CurrentItemData, DropOperation->FromSlotIndex);
                bool bDidSwapLocal = InventoryComponent->AddItemToSlot(DropOperation->ItemData, SlotIndex);

                if (bDidSwapTarget && bDidSwapLocal) { return true; }
            }

            return false;
        }
        return false;
    }
    return false;
}
