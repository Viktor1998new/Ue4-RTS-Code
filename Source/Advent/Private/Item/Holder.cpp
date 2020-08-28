// Fill out your copyright notice in the Description page of Project Settings.

#include "Holder.h"
#include "Net/UnrealNetwork.h"


FString AHolder::GetData()
{
	return "Ammo:" + FString::FromInt(Ammo);
}

void AHolder::SetData(const FString& NewData)
{
	if (NewData.IsEmpty())
		return;

	TArray<FString> Parsed;
	NewData.ParseIntoArray(Parsed, *FString(":"), true);

	Ammo = FCString::Atoi(*Parsed[1]);
}