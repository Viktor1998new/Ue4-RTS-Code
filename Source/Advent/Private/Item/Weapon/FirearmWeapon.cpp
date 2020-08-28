// Fill out your copyright notice in the Description page of Project Settings.

#include "FirearmWeapon.h"
#include "Engine/Public/TimerManager.h"

void AFirearmWeapon::Shot(bool IsActiv)
{
	if (IsActiv) {

		if (Automatic) {
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFirearmWeapon::ShotTimer, OverTime, true);
		}
		else {
			ShotTimer();
		}
	}
	else
	{
		if (GetWorldTimerManager().IsTimerActive(UnusedHandle)) {
			GetWorldTimerManager().ClearTimer(UnusedHandle);
		}
	}
}

void AFirearmWeapon::ShotTimer() {

	if (Ammo != 0)
	{
		K2_OnShot();
		Ammo = FMath::Max<float>(Ammo - 1, 0);
		return;
	}

	GetWorldTimerManager().ClearTimer(UnusedHandle);
	OnHoderEmpty.Broadcast();
	
}

FString AFirearmWeapon::GetData()
{
	return "Ammo:" + FString::FromInt(Ammo) + ",Strength:" + FString::SanitizeFloat(Strength);
}

void AFirearmWeapon::SetData(const FString& NewData)
{
	if (NewData.IsEmpty())
		return;

	TArray<FString> Parsed;
	NewData.ParseIntoArray(Parsed, *FString(","), true);

	if (!Parsed.IsValidIndex(0))
		return;

	for (int i = 0; i < Parsed.Num(); i++)
	{
		TArray<FString> SesParsed;
		Parsed[i].ParseIntoArray(SesParsed, *FString(":"), true);
		
		if(SesParsed[0] == "Ammo")
		Ammo = FCString::Atoi(*SesParsed[1]);
		
		if (SesParsed[0] == "Strength")
			Strength = FCString::Atoi(*SesParsed[1]);
	}
}

void AFirearmWeapon::Recharge(const FString & NewData)
{
	if (NewData.IsEmpty())
		return;

	TArray<FString> Parsed;
	NewData.ParseIntoArray(Parsed, *FString(":"), true);

	Ammo = FCString::Atoi(*Parsed[1]);
}

TSubclassOf<AHolder> AFirearmWeapon::GetCurrentHulder(FString& Data) {

	Data = "Ammo:" + FString::FromInt(Ammo);

	return Holder;
}