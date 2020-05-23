// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "Items/CesItem.h"


UCesItem::UCesItem()
{
    IsStackable = false;
}


FPrimaryAssetId UCesItem::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(ItemType, GetFName());
}
