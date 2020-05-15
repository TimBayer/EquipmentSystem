// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "Items/CesItem.h"


UCesItem::UCesItem()
{
    Weight = 0;
    BagSize = FVector2D(1, 1);
}


FPrimaryAssetId UCesItem::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(ItemType, GetFName());
}
