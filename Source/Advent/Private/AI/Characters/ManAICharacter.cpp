// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Characters/ManAICharacter.h"
#include "Player/BasicPlayerController.h"
#include "Inventory/InventoryComponent.h"
#include "Components/ClothesComponent.h"
#include "Components/CharacteristicComponent.h"
#include "AI/ManAIController.h"

AManAICharacter::AManAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	ClothesComponent = CreateDefaultSubobject<UClothesComponent>(TEXT("ClothesComponent"));
	CharacteristicComponent = CreateDefaultSubobject<UCharacteristicComponent>(TEXT("CharacteristicComponent"));
}

bool AManAICharacter::IsCommand(FLinearColor Verifiable)
{
	return Command == Verifiable;
}

EPriorities AManAICharacter::GetPriorities() {
	if (Cast<AManAIController>(GetController())) {
		return Cast<AManAIController>(GetController())->Priorities;
	}
	return EPriorities::P_None;
}

void AManAICharacter::SetPriorities(EPriorities NewPriorities) {
	
	if (Cast<AManAIController>(GetController())) {
		 Cast<AManAIController>(GetController())->Priorities = NewPriorities;
	}
}

void AManAICharacter::SetCommand(ABasicPlayerController * PlayerController, bool AI)
{
	if (GIsServer) {
		
		if (AI) {
			Command = FLinearColor(0,0,0,0);
			return;
		}

		Command = PlayerController->Command;
	}
}

void AManAICharacter::SetSelectEnabled(bool NewEnable)
{
	ReceiveSelectEnabled(NewEnable);
}

void AManAICharacter::SetTarget(FVector Destination, AActor * ActorTarget, bool Run)
{
	ReceiveSetTarget(Destination, ActorTarget, Run);
}
