// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "FirearmWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoderEmpty);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, abstract)
class ADVENT_API AFirearmWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AHolder> Holder;

		FTimerHandle UnusedHandle;

	UPROPERTY(EditDefaultsOnly)
		bool Automatic;

	UPROPERTY(EditDefaultsOnly)
		float OverTime;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		int Ammo;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float Strength;
	
	UFUNCTION()
		void ShotTimer();

		virtual void Shot(bool IsActiv) override;

		virtual FString GetData() override;

		virtual void SetData(const FString& NewData) override;

		FOnHoderEmpty OnHoderEmpty;

	UFUNCTION(BlueprintCallable)
		void Recharge(const FString& HoiderData);

	UFUNCTION(BlueprintPure)
		TSubclassOf<AHolder> GetCurrentHulder(FString& Data);

};
