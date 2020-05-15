// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "Core/CesPlayerController.h"
#include "Inventory/CesInventoryComponent.h"


ACesPlayerController::ACesPlayerController()
{
    // Setup Components
    InventoryComponent = CreateDefaultSubobject<UCesInventoryComponent>(TEXT("InventoryComponent"));

    bShowMouseCursor = true;
}


void ACesPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    SetInputMode(FInputModeGameAndUI()); 
}
