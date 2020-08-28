// Fill out your copyright notice in the Description page of Project Settings.

#include "Clothes.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

AClothes::AClothes() {

	bReplicates = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(DefaultSceneRoot);
}

void AClothes::SetUnitClothes(bool NewUnitClothes)
{
	UnitClothes = NewUnitClothes;
}

FString AClothes::GetData()
{
	return "Strength:" + FString::SanitizeFloat(Strength);
}

void AClothes::SetData(const FString& NewData)
{
	if (NewData.IsEmpty())
		return;

	TArray<FString> Parsed;
	NewData.ParseIntoArray(Parsed, *FString(","), true);

	for (int i = 0; i < Parsed.Num(); i++)
	{
		TArray<FString> SesParsed;
		Parsed[i].ParseIntoArray(SesParsed, *FString(":"), true);

		if (SesParsed[0] == "Strength")
			Strength = FCString::Atoi(*SesParsed[1]);
	}
}
