// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "CesAssetManager.h"
#include "Engine/DataAsset.h"
#include "CesItem.generated.h"

/**
 * Base Class for all game items
 */
UCLASS(Abstract, BlueprintType)
class EQUIPMENTSYSTEM_API UCesItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UCesItem();

    FPrimaryAssetId GetPrimaryAssetId() const override;

    // The Primary Asset Type of this item.  The Primary Asset Type must be added to the Asset Manager
    // under Project Settings to be a selectable Item Type.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
    FPrimaryAssetType ItemType;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FSlateBrush ItemIcon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    int32 Weight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FVector2D BagSize;

    // The type of slots this item is allowed to be placed in
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory Slot")
    EInvSlotAllowance SlotAllowance;
};
