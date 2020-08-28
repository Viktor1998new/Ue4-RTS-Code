// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

ABasicAIController::ABasicAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}
