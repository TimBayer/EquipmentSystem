// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesInventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemAdded, int32, SlotIndex, FCesItemData, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemRemoved, int32, SlotIndex, FCesItemData, Item);


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EQUIPMENTSYSTEM_API UCesInventoryComponent : public UActorComponent
{
    GENERATED_BODY()


public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TArray<FCesItemData> Items;

    // Add a item to the next available slot
    UFUNCTION(BlueprintCallable, Category = Inventory, meta = (DisplayName = "AddItem"))
    bool AddItem(FCesItemData ItemData);

    // Attempt to add an item to a specific slot
    UFUNCTION(BlueprintCallable, Category = Inventory, meta = (DisplayName = "AddItem"))
    bool AddItemToSlot(FCesItemData ItemData, int32 SlotIndex);

    // Clear the item from a slot
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool EmptySlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool IsSlotFilled(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = Inventory)
    int32 GetSlotCount() const { return SlotCount; }

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
    int32 InitialSlotCount;

    UPROPERTY(BlueprintAssignable)
    FOnInventoryItemAdded OnInventoryItemAdded;

    UPROPERTY(BlueprintAssignable)
    FOnInventoryItemRemoved OnInventoryItemRemoved;


protected:
    virtual void BeginPlay() override;


private:
    int32 SlotCount;

    bool IsValidSlot(int32 SlotIndex) const;
};
