// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceSelectPawn.generated.h"

class AActor;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceSelectPawn : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ADVENT_API IInterfaceSelectPawn
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SelectPawn")
		 void SetTarget(FVector Destination, AActor* ActorTarget,bool Run);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SelectPawn")
		bool IsCommand(FLinearColor ColorCommand);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SelectPawn")
		bool IsDeath();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SelectPawn")
		bool IsUseVehicle();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SelectPawn")
		 void SetSelectEnabled(bool NewEnable);

};
