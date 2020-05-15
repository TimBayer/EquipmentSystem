// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "CesAssetManager.h"
#include "EquipmentSystem.h"


const FPrimaryAssetType UCesAssetManager::ConsumableItemType = TEXT("ConsumableItem");
const FPrimaryAssetType UCesAssetManager::EquipableItemType = TEXT("EquipableItem");


UCesAssetManager& UCesAssetManager::Get()
{
    UCesAssetManager* This = Cast<UCesAssetManager>(GEngine->AssetManager);

    if (This)
    {
        return *This;
    }

    UE_LOG(CesLog, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini."));

    // Should never reach this
    return *NewObject<UCesAssetManager>();
}
