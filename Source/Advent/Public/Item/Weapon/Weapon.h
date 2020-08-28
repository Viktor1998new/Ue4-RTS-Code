// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Inventory/ItemActor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8 {

	W_None 	UMETA(DisplayName = "None"),
	W_Basic 	UMETA(DisplayName = "Basic"),
	W_Additional 	UMETA(DisplayName = "Additional"),
	W_SteelArms	UMETA(DisplayName = "SteelArms")
};

UCLASS(NotBlueprintable,abstract)
class ADVENT_API AWeapon : public AItemActor
{
	 GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EWeaponType WeaponType;

	UPROPERTY()
		bool UnitClothes;

	UFUNCTION(BlueprintPure)
		bool IsUnitClothes()const { return UnitClothes; }


	void SetUnitClothes(bool NewUnitClothes);


	UFUNCTION(BlueprintCallable, Category = Weapon)
		virtual void Shot(bool IsActiv);

	virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps)  const override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "OnShot"))
		void K2_OnShot();
};
