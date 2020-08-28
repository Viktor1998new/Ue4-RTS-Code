// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "BasicVehicle.generated.h"


class AManAICharacter;
class UInventoryComponent;

USTRUCT(BlueprintInternalUseOnly)
struct FPlaceStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
		FVector PlaceLocation;

	UPROPERTY(EditDefaultsOnly)
		FVector ExitLocation;

	UPROPERTY(EditDefaultsOnly)
		bool Visibility = true;

	AManAICharacter* Man;
};
/**
 * 
 */
UCLASS(abstract)
class ADVENT_API ABasicVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

public:

	ABasicVehicle(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(Category = Components, BlueprintReadOnly, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		UInventoryComponent * InventoryComponent;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TArray<FPlaceStruct> Places;

		bool GetPlace(int &IndexPlaces);
	
	UFUNCTION(BlueprintCallable)
		bool UseVehicle(AManAICharacter* ManCharacter);

	UFUNCTION(BlueprintCallable)
		void ExitVehicle(AManAICharacter* ManCharacter);


};
