// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicAICharacter.generated.h"

UCLASS(abstract)
class ADVENT_API ABasicAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicAICharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
		virtual void SetEnableRun(bool Enable);

	UFUNCTION(BlueprintCallable)
		virtual void Attack(bool Active);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Attack"))
		void ReceiveAttack(bool Active);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetEnableRun"))
		void ReceiveSetEnableRun(bool Enable);

	UFUNCTION(BlueprintPure)
		virtual bool IsDeath();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "IsDeath"))
		bool ReceiveIsDeath();

};
