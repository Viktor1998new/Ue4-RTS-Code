// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAIController.h"
#include "AI/Characters/BasicAICharacter.h"
#include "AI/Characters/ManAICharacter.h"
#include "ManAIController.generated.h"

/**
 * 
 */
UCLASS()
class ADVENT_API AManAIController : public ABasicAIController
{
	GENERATED_BODY()

		
public:
	AManAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintReadWrite)
		EPriorities Priorities;

	UPROPERTY(BlueprintReadOnly)
		TArray<ABasicAICharacter* > Enemys;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName NameKeyActorTarget;
	
	UFUNCTION(BlueprintPure)
		bool IsEnemy(ABasicAICharacter* PawnCharacter);

	UFUNCTION(BlueprintCallable)
		void AddEnemy(ABasicAICharacter* PawnCharacter);

	UFUNCTION(BlueprintCallable)
		ABasicAICharacter* FindEnemy();

protected:

	UPROPERTY(BlueprintReadOnly)
		AManAICharacter* PawnMan;

	virtual void OnPossess(APawn* InPawn) override;
};
