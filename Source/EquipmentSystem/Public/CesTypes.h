// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CesTypes.generated.h"


UENUM(BlueprintType)
enum class EEquipmentSlotType : uint8
{
    MainHand,
    OffHand,
    Helmet,
    Chest,
    Legs,
    Hands,
    Feet,
    Ring,
    Amulet
};


UENUM(BlueprintType)
enum class EArmorItemType : uint8
{
    Helmet,
    Chest,
    Legs,
    Hands,
    Feet,
    Ring,
    Amulet
};


UENUM(BlueprintType)
enum class EWeaponItemType : uint8
{
    Dagger,
    Sword,
    Axe,
    Hammer
};


UENUM(BlueprintType)
enum class EAccessoryItemType : uint8
{
    Ring,
    Amulet
};


UENUM(BlueprintType)
enum class EConsumableType : uint8
{
    Currency,
    Potion,
    Food,
    Drink,
    Book,
    Scroll
};


/**
 * Used to determine what type of item is allowed to be placed in an item slot
 */
UENUM(BlueprintType)
enum class EInvSlotAllowance : uint8
{
    AllItems,
    Consumable,
    Weapon,
    Helmet,
    Chest,
    Legs,
    Hands,
    Feet,
    Ring,
    Amulet
};


USTRUCT(BlueprintType)
struct EQUIPMENTSYSTEM_API FCesItemData
{
    GENERATED_BODY()


    FCesItemData()
        : Item(nullptr), Quantity(0)
    {
    }


    FCesItemData(class UCesItem* InItem, int32 InQuantity)
        : Item(InItem), Quantity(InQuantity)
    {
    }


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    class UCesItem* Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    int32 Quantity;


    bool operator==(const FCesItemData& OtherItem) const
    {
        return Item == OtherItem.Item;
    }


    bool operator!=(const FCesItemData& OtherItem) const
    {
        return !(*this == OtherItem);
    }


    // Is this a valid item
    bool IsValid() const
    {
        return (Item != nullptr && Quantity > 0);
    }
};


USTRUCT(BlueprintType)
struct EQUIPMENTSYSTEM_API FCesEquipmentStats
{
    GENERATED_BODY()


    FCesEquipmentStats()
        : Damage(0), Armor(0)
    {
    }


    FCesEquipmentStats(float InDamage, float InArmor)
        : Damage(0), Armor(0)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    float Armor;
};
