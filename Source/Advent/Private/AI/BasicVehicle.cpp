// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicVehicle.h"
#include "AI/Characters/ManAICharacter.h"
#include "Inventory/InventoryComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WheeledVehicleMovementComponent.h"

ABasicVehicle::ABasicVehicle(const FObjectInitializer& ObjectInitializer)
{

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

bool ABasicVehicle::GetPlace(int &IndexPlaces)
{
	for (int i = 0; i < Places.Num(); i++)
	{
		if (!IsValid(Places[i].Man)) {
			IndexPlaces = i;
			return true;
		}
	}
	return false;
}

bool ABasicVehicle::UseVehicle(AManAICharacter * ManCharacter)
{
	int L_IndexPlace;

		if (GetPlace(L_IndexPlace)&& GetVehicleMovement()->GetForwardSpeed() == 0) {
			
			ManCharacter->IsUseVehicle = true;
			Places[L_IndexPlace].Man = ManCharacter;
			
			ManCharacter->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, NAME_None);

			if (!Places[L_IndexPlace].Visibility) {
				ManCharacter->GetMesh()->SetVisibility(false);
			}
			else {
				ManCharacter->SetActorRelativeLocation(Places[L_IndexPlace].PlaceLocation);
				ManCharacter->SetActorRelativeRotation(FRotator(0, 0, 0));
			}

			return true;
		}

	return false;
}

void ABasicVehicle::ExitVehicle(AManAICharacter * ManCharacter)
{
	for (int i = 0; i < Places.Num(); i++)
	{
		if (IsValid(Places[i].Man)) {
			
			if (Places[i].Man == ManCharacter) {
				Places[i].Man = nullptr;
				ManCharacter->IsUseVehicle = false;
				ManCharacter->SetActorRelativeLocation(Places[i].ExitLocation);
				ManCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				ManCharacter->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}
