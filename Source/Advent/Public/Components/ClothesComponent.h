// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/Weapon/FirearmWeapon.h"
#include "Item/Weapon/Weapon.h"
#include "Item/Clothes.h"
#include "ClothesComponent.generated.h"

class ACharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewBackpack);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENT_API UClothesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
		
	ACharacter * CurrentCharacter;

	UPROPERTY(EditDefaultsOnly, Category = Socekts)
		FName NameSocektForWeapon;

	UPROPERTY(EditDefaultsOnly, Category = Socekts)
		FName NameSocektHolsterForBasicWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = Socekts)
		FName NameSocektHolsterForAdditionalWeapon;

	UPROPERTY(EditDefaultsOnly, Category = Socekts)
		FName NameSocektHolsterForSteelArmsWeapon;

	UPROPERTY(Replicated)
		TArray<AClothes *> CurrentsClothes;

	/*----------------------------------------------*/

	UPROPERTY(Replicated)
		TArray<AWeapon*> CurrentWeapons;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Replicated, Category = Weapon)
		EWeaponType SelectWeapon;

	// Sets default values for this component's properties
	UClothesComponent();

protected:

	virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps)  const override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = Clothes)
		void SetClothes(TSubclassOf<AClothes> Class, FString Data);
	
	UFUNCTION(BlueprintCallable, Category = Clothes)
		AClothes* GetCurrentClothes(EEquipPart Type);

	UFUNCTION(BlueprintCallable, Category = Clothes)
		void ClearClothes(EEquipPart Type);

	/*------------------------------------------------------------------------------*/

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetWeapon(TSubclassOf<AWeapon> Class, FString Data);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetSelectWeapon(EWeaponType NewSelect);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void ClearWeapon(EWeaponType Type);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		AWeapon* GetCurrentWeapon(EWeaponType Type);

	UFUNCTION(BlueprintCallable, Category = Weapon)
		AWeapon* GetSelectWeapon();

	UPROPERTY(BlueprintAssignable)
		FOnHoderEmpty OnHoderEmpty;

	UFUNCTION(BlueprintCallable)
		void Recharge();

};
