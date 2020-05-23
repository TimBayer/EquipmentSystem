// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CesInventoryComponent.h"

#include "CesItemSlotWidget.generated.h"



UCLASS(Abstract)
class EQUIPMENTSYSTEM_API UCesItemSlotWidget : public UUserWidget
{
    GENERATED_BODY()


public:
    // InventoryComponent this slot belongs to
    UPROPERTY(BlueprintReadOnly, Category="Inventory Slot", meta=( ExposeOnSpawn="true"))
    UCesInventoryComponent* InventoryComponent;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UCesItemDragVisual> ItemDragVisualClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Slot", meta=( ExposeOnSpawn="true", DisplayName= "Item Data" ))
    FCesItemData ItemData;

    // The type of item this slot accepts
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Slot", meta=( ExposeOnSpawn="true"))
    EInvSlotAllowance SlotAllowance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Slot", meta=( ExposeOnSpawn="true"))
    int32 SlotIndex;

    UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    void SetInventoryComponent(UCesInventoryComponent* NewInventoryComponent);
    
    UFUNCTION()
    void OnItemAddedNative(int32 AddedItemSlotIndex, FCesItemData AddedItem);

    UFUNCTION(BlueprintImplementableEvent, Category = "Inventory Slot")
    void OnItemAdded(FCesItemData Item);

    UFUNCTION()
    void OnItemRemovedNative(int32 RemovedSlotIndex, FCesItemData RemovedItem);

    UFUNCTION(BlueprintImplementableEvent, Category = "Inventory Slot")
    void OnItemRemoved();


protected:
    virtual void NativeConstruct() override;

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    // Executes on the widget the drop finished on
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UDragDropOperation* CreateItemDrag();

private:
    
};
