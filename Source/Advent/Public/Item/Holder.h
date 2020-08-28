// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemActor.h"
#include "Holder.generated.h"

class ACartridge;
/**
 *  
 */

UCLASS(abstract)
class ADVENT_API AHolder : public AItemActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
		int Ammo;

	UPROPERTY(EditDefaultsOnly)
		int MaxAmmo;

	virtual void SetData(const FString& NewData) override;

	virtual FString GetData() override;
	
};

