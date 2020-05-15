// Copyright 2020 Tim Bayer. All Rights Reserved.


#include "Core/CesPawn.h"
#include "SpineSkeletonAnimationComponent.h"
#include "SpineSkeletonRendererComponent.h"


ACesPawn::ACesPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Setup Root
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // Setup Spine components
    SkeletonRendererComponent = CreateDefaultSubobject<USpineSkeletonRendererComponent>(TEXT("SpineSkeletonRenderer"));
    SkeletonRendererComponent->SetupAttachment(RootComponent);

    SkeletonAnimationComponent = CreateDefaultSubobject<USpineSkeletonAnimationComponent>(TEXT("SpineSkeletonAnimation"));
}


void ACesPawn::BeginPlay()
{
    Super::BeginPlay();
}
