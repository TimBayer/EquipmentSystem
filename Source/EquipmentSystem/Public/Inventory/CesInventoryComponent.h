// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "CesInventoryInterface.h"
#include "EquipmentSystem.h"
#include "CesInventoryComponent.generated.h"


// Event for inventory change
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryChanged);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EQUIPMENTSYSTEM_API UCesInventoryComponent : public UActorComponent
{
    GENERATED_BODY()


public:
    UCesInventoryComponent();

    /**
     * Map of all inventory slots and the items in those slots
     * <slot ID, Item>
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<int32, FCesItemData> SlottedItems;
    
    // Add a item to the next available slot
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool AddItem(FCesItemData ItemData);

    // Attempt to add an item to a specific slot
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool AddItemToSlot(FCesItemData ItemData, int32 Slot);

    // Clear the item from a slot
    UFUNCTION(BlueprintCallable, Category = Inventory)
    void EmptySlot(int32 Slot);
    
    UPROPERTY(BlueprintAssignable)
    FInventoryChanged OnInventoryChanged;

    UFUNCTION(BlueprintCallable, Category = Inventory)
    int32 GetTotalSlotCount() const { return SlotCount; }

    
protected:
    virtual void BeginPlay() override;

    
private:
    int32 SlotCount;
};
