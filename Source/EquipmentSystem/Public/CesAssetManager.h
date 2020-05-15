// Copyright 2020 Tim Bayer. All Rights Reserved.

#pragma once

#include "EquipmentSystem.h"
#include "Engine/AssetManager.h"
#include "CesAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class EQUIPMENTSYSTEM_API UCesAssetManager : public UAssetManager
{
    GENERATED_BODY()

public:
    static const FPrimaryAssetType ConsumableItemType;
    static const FPrimaryAssetType EquipableItemType;

    static UCesAssetManager& Get();
};
