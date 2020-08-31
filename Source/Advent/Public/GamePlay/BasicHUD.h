// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AI/Characters/ManAICharacter.h"
#include "BasicHUD.generated.h"

class APawn;
/**
 * 
 */
UCLASS()
class ADVENT_API ABasicHUD : public AHUD
{
	GENERATED_BODY()
	
		TArray<APawn*> Selects;
		bool Select;
		FVector2D InitialPoint;

public:

	virtual void DrawHUD() override;

	void SelectEnable();

	void SelectDisable(bool &IsSelectNull, TArray<APawn*> &SelectUnit);
};
