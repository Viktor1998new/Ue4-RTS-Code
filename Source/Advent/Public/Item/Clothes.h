// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemActor.h"
#include "Clothes.generated.h"

class USkeletalMeshComponent;
class USceneComponent;
class UClothesComponent;

UENUM(BlueprintType)
enum class EEquipPart : uint8 {

	C_Head 	UMETA(DisplayName = "Head"),
	C_Face 	UMETA(DisplayName = "Face"),
	C_Defense 	UMETA(DisplayName = "Defense"),
	C_Jacket 	UMETA(DisplayName = "Jacket"),
	C_Pants 	UMETA(DisplayName = "Pants"),
};

UCLASS(abstract)
class ADVENT_API AClothes : public AItemActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EEquipPart EquipPart;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent * DefaultSceneRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent * Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float Strength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Infection;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Bullets;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Explosive;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float MeleeWeapons;

	AClothes();

	UPROPERTY()
		bool UnitClothes;

	UFUNCTION(BlueprintPure)
		bool IsUnitClothes()const { return UnitClothes; }

		void SetUnitClothes(bool NewUnitClothes);

		virtual FString GetData() override;
		
		virtual void SetData(const FString& NewData) override;
};

