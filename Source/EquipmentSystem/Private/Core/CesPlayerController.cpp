// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "Core/CesPlayerController.h"



ACesPlayerController::ACesPlayerController()
{
    bShowMouseCursor = true;
}


void ACesPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameAndUI());
}