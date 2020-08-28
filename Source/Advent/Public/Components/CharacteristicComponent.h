// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumingItem.h"
#include "Components/ActorComponent.h"
#include "CharacteristicComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), NotBlueprintable)
class ADVENT_API UCharacteristicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Health)
		float MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Health)
		float Health = 100;

	//The calculation formula of 1/ Seconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		float SpeedHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Endurance)
		float MaxEndurance = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Endurance)
		float Endurance = 100;

	//The calculation formula of 1/ Seconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Endurance)
		TMap<FName, float> SpeedEndurance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Agility)
		float SpeedUseItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = PortableWeight)
		float PortableWeight;

	FName StaticEndurance = "Default";

	bool IsDead;

	FTimerHandle EnduranceTimer;

	FTimerHandle HealthTimer;

	// Sets default values for this component's properties
	UCharacteristicComponent();

protected:

	virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps)  const override;

public:	

	UPROPERTY(BlueprintAssignable)
		FDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
		FDeath EnduranceEnd;


	UFUNCTION(BlueprintCallable, Category = "Calculate|Math|Characteristic")
		void CalculateHealth(float Value);

	UFUNCTION(BlueprintCallable, Category = "Calculate|Math|Characteristic")
		void CalculateEndurance(float Value);

	UFUNCTION(BlueprintCallable)
		void SetStaticEndurance(FName NewStatic);

	virtual void BeginPlay() override;

	void TickEndurance();

	void TickHealth();

	UFUNCTION(BlueprintCallable)
		bool UseConsumingItem(TSubclassOf<AConsumingItem> Class);

	UFUNCTION(BlueprintPure)
		bool GetIsDead() const {
			return IsDead;
		}
};
