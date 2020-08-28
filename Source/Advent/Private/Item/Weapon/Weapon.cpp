// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "UnrealNetwork.h"

void AWeapon::Shot(bool IsActiv) {
	K2_OnShot();
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void AWeapon::SetUnitClothes(bool NewUnitClothes)
{
	UnitClothes = NewUnitClothes;
}