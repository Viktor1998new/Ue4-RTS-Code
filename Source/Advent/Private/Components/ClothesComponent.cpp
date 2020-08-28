// Fill out your copyright notice in the Description page of Project Settings.

#include "ClothesComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "AI/Characters/ManAICharacter.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UClothesComponent::UClothesComponent()
{
	SetIsReplicatedByDefault(true);

}

void UClothesComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UClothesComponent, CurrentWeapons);
	DOREPLIFETIME(UClothesComponent, CurrentsClothes);
	DOREPLIFETIME(UClothesComponent, SelectWeapon);
}

// Called when the game starts
void UClothesComponent::BeginPlay()
{
	if (!Cast<ACharacter>(GetOwner()))
	{
		DestroyComponent();
		return;
	}

	CurrentCharacter = Cast<ACharacter>(GetOwner());
}

void UClothesComponent::SetSelectWeapon(EWeaponType NewSelect) {

	if (NewSelect == SelectWeapon)
		return;

	if(!IsValid(CurrentCharacter))
		CurrentCharacter = Cast<ACharacter>(GetOwner());
		
	AWeapon* NewSelectWeapon = GetCurrentWeapon(NewSelect);
	
	if (NewSelect != EWeaponType::W_None) {
	
		if (IsValid(NewSelectWeapon)) {

			NewSelectWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektForWeapon);
			NewSelectWeapon->SetActorRelativeLocation(FVector::ZeroVector);
			NewSelectWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);
			
		}
	}

	AWeapon* L_CurrentWeapon = GetCurrentWeapon(SelectWeapon);

	if (IsValid(L_CurrentWeapon)) {

		switch (SelectWeapon)
		{
		case EWeaponType::W_Basic:
			L_CurrentWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektHolsterForBasicWeapon);
			break;

		case EWeaponType::W_Additional:
			L_CurrentWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektHolsterForAdditionalWeapon);
			break;

		case EWeaponType::W_SteelArms:
			L_CurrentWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektHolsterForSteelArmsWeapon);
			break;
		}

		L_CurrentWeapon->SetActorRelativeLocation(FVector::ZeroVector);
		L_CurrentWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);
	}

	SelectWeapon = NewSelect;
}

void UClothesComponent::SetClothes(TSubclassOf<AClothes> Class, FString Data)
{
	if (!GIsServer) {
		return;
	}

	if (!IsValid(Class)) {
		return;
	}

	if (!IsValid(CurrentCharacter))
		CurrentCharacter = Cast<ACharacter>(GetOwner());

	auto const World = GetWorld();
	const FTransform SpawnTransform = FTransform::Identity;

	auto const NewClothes = World->SpawnActorDeferred<AClothes>(Class, SpawnTransform);

	NewClothes->SetUnitClothes(true);

	NewClothes->SetData(Data);

	NewClothes->FinishSpawning(SpawnTransform);

	NewClothes->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NAME_None);

	if (AClothes* CurrentClothes = GetCurrentClothes(NewClothes->EquipPart)) {

		int AddIndex;

		if (Cast<AManAICharacter>(CurrentCharacter)->InventoryComponent->AddActorItem(CurrentClothes, AddIndex))
		{
			CurrentClothes->Destroy();
		}
		else {
			CurrentClothes->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			CurrentClothes->SetUnitClothes(false);
		}

		CurrentsClothes.Remove(CurrentClothes);
	}

	CurrentsClothes.Add(NewClothes);
}


AClothes * UClothesComponent::GetCurrentClothes(EEquipPart Type)
{
	if (CurrentsClothes.IsValidIndex(0)) {
		for (int i = 0; i < CurrentsClothes.Num(); i++)
		{
			if (CurrentsClothes[i]->EquipPart == Type) {
				return CurrentsClothes[i];
			}
		}
	}
	return nullptr;
}

void UClothesComponent::ClearClothes(EEquipPart Type)
{
	if (!GIsServer) {
		return;
	}

	if (AClothes* CurrentClothes = GetCurrentClothes(Type))
	{
		CurrentsClothes.Remove(CurrentClothes);
		CurrentClothes->Destroy();
	}
}

void UClothesComponent::SetWeapon(TSubclassOf<AWeapon> Class, FString Data)
{
	if (!GIsServer) {
		return;
	}

	if (!IsValid(Class)) {
		return;
	}

	if(!IsValid(CurrentCharacter))
		CurrentCharacter = Cast<ACharacter>(GetOwner());
		
	const FTransform SpawnTransform = FTransform::Identity;

	AWeapon* NewWeapon = GetWorld()->SpawnActorDeferred<AWeapon>(Class, FTransform::Identity);

	NewWeapon->SetUnitClothes(true);

	NewWeapon->SetData(Data);

	NewWeapon->FinishSpawning(FTransform::Identity);
		
	if (NewWeapon->WeaponType == SelectWeapon) {
			NewWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektForWeapon);
			NewWeapon->SetActorRelativeLocation(FVector::ZeroVector);
			NewWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);
	}
	else {
		
		switch (NewWeapon->WeaponType)
		{
			case EWeaponType::W_Basic:
				NewWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektHolsterForBasicWeapon);
				break;
			case EWeaponType::W_Additional:
				NewWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektHolsterForAdditionalWeapon);
				break;
			case EWeaponType::W_SteelArms:
				NewWeapon->AttachToComponent(CurrentCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, NameSocektHolsterForSteelArmsWeapon);
				break;
		}
		NewWeapon->SetActorRelativeLocation(FVector::ZeroVector);
		NewWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);
			
	}
		
	if (CurrentWeapons.IsValidIndex(0)) {
		
		if (IsValid(GetCurrentWeapon(NewWeapon->WeaponType))) {
			
			AWeapon* CurrentWeapon = GetCurrentWeapon(NewWeapon->WeaponType);

			int32 AddIndex;
			if (Cast<AManAICharacter>(CurrentCharacter)->InventoryComponent->AddActorItem(CurrentWeapon, AddIndex))
			{
				CurrentWeapon->Destroy();
			}
			else {
				CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				CurrentWeapon->SetUnitClothes(false);
			}

		if (Cast<AFirearmWeapon>(CurrentWeapon))
			Cast<AFirearmWeapon>(CurrentWeapon)->OnHoderEmpty.RemoveDynamic(this, &UClothesComponent::Recharge);

		CurrentWeapons.Remove(CurrentWeapon);
		
		}
		
		if(Cast<AFirearmWeapon>(NewWeapon))
			Cast<AFirearmWeapon>(NewWeapon)->OnHoderEmpty.AddDynamic(this, &UClothesComponent::Recharge);

		CurrentWeapons.Add(NewWeapon);

	}
}

void UClothesComponent::Recharge() {
	OnHoderEmpty.Broadcast();
}

AWeapon* UClothesComponent::GetCurrentWeapon(EWeaponType Type) {

	if (CurrentWeapons.IsValidIndex(0)) {
		for (int i = 0; i < CurrentWeapons.Num(); i++)
		{
			if (CurrentWeapons[i]->WeaponType == Type) {

				return CurrentWeapons[i];
			}
		}
	}
	return nullptr;
}

AWeapon * UClothesComponent::GetSelectWeapon()
{
	if (CurrentWeapons.IsValidIndex(0)) {
		for (int i = 0; i < CurrentWeapons.Num(); i++)
		{
			if (CurrentWeapons[i]->WeaponType == SelectWeapon) {
				return CurrentWeapons[i];
			}
		}
	}
	return nullptr;
}

void UClothesComponent::ClearWeapon(EWeaponType Type) {

	if (!GIsServer) {
		return;
	}

	if (AWeapon* CurrentWeapon = GetCurrentWeapon(Type))
	{
		CurrentWeapons.Remove(CurrentWeapon);
		CurrentWeapon->Destroy();
	}
}