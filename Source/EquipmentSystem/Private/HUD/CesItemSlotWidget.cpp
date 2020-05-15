// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "HUD/CesItemSlotWidget.h"
#include "Components/Image.h"
#include "HUD/CesDragDropItem.h"
#include "HUD/CesItemDragVisual.h"
#include "Items/CesItem.h"


void UCesItemSlotWidget::NativeConstruct()
{
    Inventory = GetOwningPlayer()->FindComponentByClass<UCesInventoryComponent>();
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


void UCesItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    // Set input to UI only on drag so we don't affect game
    GetOwningPlayer()->SetInputMode(FInputModeUIOnly());

    OutOperation = CreateItemDrag();
}


UDragDropOperation* UCesItemSlotWidget::CreateItemDrag()
{
    UCesDragDropItem* DragDropOperation = NewObject<UCesDragDropItem>();

    if (ItemData.Item && ItemData.Quantity > 0)
    {
        if (ItemDragVisualClass)
        {
            // Add the actual item data to the drag operation
            DragDropOperation->ItemData = ItemData;

            // Create and populate the widget we see while dragging
            UCesItemDragVisual* DragVisual = CreateWidget<UCesItemDragVisual>(GetOwningPlayer(), ItemDragVisualClass);
            DragVisual->ItemData = ItemData;

            DragDropOperation->DefaultDragVisual = DragVisual;
            DragDropOperation->Pivot = EDragPivot::MouseDown;
            DragDropOperation->FromSlot = this;

            // Notify Blueprints Item was removed
            ItemDragStarted();
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

    ItemDragCancelled();

    // Set input mode back
    GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
    
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Item Dropped Cancelled!"));
}


bool UCesItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    // Set input mode back
    GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());

    if (!Inventory)
    {
        UE_LOG(CesLog, Error, TEXT("UCesItemSlotWidget::NativeOnDrop - InventoryComponent not found!"))
    }
    
    UCesDragDropItem* DropOperation = Cast<UCesDragDropItem>(InOperation);
    if (DropOperation && DropOperation->ItemData.Quantity > 0)
    {
        if (SlotAllowance == EInvSlotAllowance::AllItems || DropOperation->ItemData.Item->SlotAllowance == SlotAllowance)
        { 
            // Add item to new slot
            const bool bItemAdded = Inventory->AddItemToSlot(DropOperation->ItemData, SlotIndex);

            if (bItemAdded)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green,
                    FString::Printf(TEXT("%s dropped to %s slot. (Allowed)"), *DropOperation->ItemData.Item->ItemName.ToString(), *this->GetLabelText().ToString()));
                
                
                // Remove item from previous Inventory slot
                Inventory->EmptySlot(DropOperation->FromSlot->SlotIndex);

                // Let previous slot widget know item was removed
                DropOperation->FromSlot->ItemRemoved();
                    
                // Notify Blueprints Item was added
                ItemAdded();

                return true;
            }

           return false;
        }
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green,
                            FString::Printf(TEXT("%s dropped to %s slot. (Denied)"), *DropOperation->ItemData.Item->ItemName.ToString(), *this->GetLabelText().ToString()));
    }
    return false;
}
