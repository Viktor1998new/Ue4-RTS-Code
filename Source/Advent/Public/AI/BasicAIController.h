// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicAIController.generated.h"

/**
 * 
 */
UCLASS()
class ADVENT_API ABasicAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABasicAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
