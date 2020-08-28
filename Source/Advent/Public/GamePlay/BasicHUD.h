// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AI/Characters/ManAICharacter.h"
#include "BasicHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADVENT_API ABasicHUD : public AHUD
{
	GENERATED_BODY()
	
		TArray<AManAICharacter*> Selects;
		bool Select;
		FVector2D InitialPoint;

public:

	virtual void DrawHUD() override;

	void SelectEnable();

	void SelectDisable(bool &IsSelectNull, TArray<AManAICharacter*> &SelectUnit);
};
