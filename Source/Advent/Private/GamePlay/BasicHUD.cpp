// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlay/BasicHUD.h"

void ABasicHUD::DrawHUD() {

	if (Select) {
		
		FVector2D MousePosition;
		PlayerOwner->GetMousePosition(MousePosition.X, MousePosition.Y);

		DrawRect(FLinearColor(0, 0, 1, 0.5f), InitialPoint.X, InitialPoint.Y, MousePosition.X - InitialPoint.X, MousePosition.Y - InitialPoint.Y);
		TArray<AManAICharacter*> NewSelects;
		GetActorsInSelectionRectangle<AManAICharacter>(InitialPoint,MousePosition, NewSelects,false, false);
		Selects = NewSelects;
	}

}

void ABasicHUD::SelectEnable() {

	FVector2D MousePosition;
	PlayerOwner->GetMousePosition(MousePosition.X, MousePosition.Y);
	InitialPoint = MousePosition;

	Select = true;
}

void ABasicHUD::SelectDisable(bool &IsSelectNull, TArray<AManAICharacter*> &SelectUnit) {
	
	Select = false;

	FVector2D MousePosition;
	PlayerOwner->GetMousePosition(MousePosition.X, MousePosition.Y);

	if (InitialPoint == MousePosition|| !Selects.IsValidIndex(0)) {
		IsSelectNull = true;
		InitialPoint = FVector2D::ZeroVector;
		return;
	}
	IsSelectNull = false;
	SelectUnit = Selects;
}