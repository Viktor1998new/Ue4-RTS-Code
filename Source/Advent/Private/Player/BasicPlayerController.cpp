// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPlayerController.h"
#include "GamePlay/BasicHUD.h"
#include "AI/Characters/ManAICharacter.h"
#include "Player/CameraPlayerPawn.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Engine/Public/TimerManager.h"
#include "UnrealNetwork.h"

void ABasicPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasicPlayerController, CharacterSelects);
}

void ABasicPlayerController::SetCommand(FLinearColor NewCommand)
{
	if (GIsServer) {
		Command = NewCommand;
	}
}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	bEnableClickEvents = true;
	bShowMouseCursor = true;

	InputComponent->BindAction("MouseClickLeft", IE_Pressed, this, &ABasicPlayerController::OnLeftMouseButtonPressed);
	InputComponent->BindAction("MouseClickLeft", IE_Released, this, &ABasicPlayerController::OnLeftMouseButtonReleased);

	InputComponent->BindAction("MouseClickRight", IE_Pressed, this, &ABasicPlayerController::OnRightMouseButtonPressed);
	InputComponent->BindAction("MouseClickRight", IE_Released, this, &ABasicPlayerController::OnRightMouseButtonReleased);

	InputComponent->BindAction("View", IE_Pressed, this, &ABasicPlayerController::OnViewButtonPressed);
	InputComponent->BindAction("View", IE_Released, this, &ABasicPlayerController::OnViewButtonReleased);
}

void ABasicPlayerController::OnViewButtonPressed() {
	View = true;
}

void ABasicPlayerController::OnViewButtonReleased() {
	View = false;
}

void ABasicPlayerController::OnRightMouseButtonPressed() {

	ACameraPlayerPawn* L_CameraPawn = Cast<ACameraPlayerPawn>(GetPawn());

	if (IsValid(L_CameraPawn)) {
		L_CameraPawn->IsRatation = true;

		GetMousePosition(initalMousePosition.X, initalMousePosition.Y);
		
	}
}

void ABasicPlayerController::OnRightMouseButtonReleased() {

	ACameraPlayerPawn* L_CameraPawn = Cast<ACameraPlayerPawn>(GetPawn());

	if (IsValid(L_CameraPawn)) {
		L_CameraPawn->IsRatation = false;

		FVector2D MousePosition;
		GetMousePosition(MousePosition.X, MousePosition.Y);
		
		if (initalMousePosition == MousePosition) {
			ClearListSelect();
		}
	}
}

void ABasicPlayerController::OnLeftMouseButtonPressed() {

	GetMousePosition(initalMousePosition.X, initalMousePosition.Y);
	Cast<ABasicHUD>(GetHUD())->SelectEnable();
	
	CountClick++;

	if (!GetWorldTimerManager().IsTimerActive(UnusedHandle))
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABasicPlayerController::DoubleClick, 0.50f, false);

}

void ABasicPlayerController::OnLeftMouseButtonReleased() {

	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);


	bool IsSelectNull;
	TArray<AManAICharacter*> SelectUnit;
	FHitResult L_HitMouse;
	Cast<ABasicHUD>(GetHUD())->SelectDisable(IsSelectNull, SelectUnit);

	if (FVector2D(initalMousePosition - MousePosition).Size()<5)
	{

		GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, L_HitMouse);

		if (IsValid(L_HitMouse.GetActor()) && Cast<AManAICharacter>(L_HitMouse.GetActor())) {

			if (Cast<AManAICharacter>(L_HitMouse.GetActor())->IsCommand(Command)) {

				ClearListSelect();
				TArray<AManAICharacter*> NewSelectUnit;
				NewSelectUnit.Add(Cast<AManAICharacter>(L_HitMouse.GetActor()));
				SetListSelectUnit(NewSelectUnit);
				return;
			}

			if (CharacterSelects.IsValidIndex(0)) {

				GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, L_HitMouse);
				SendUnitTarget(L_HitMouse.Location, L_HitMouse.GetActor(), false, View);

				if (CountClick >= 2) {

					GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, L_HitMouse);
					SendUnitTarget(L_HitMouse.Location, L_HitMouse.GetActor(), true, View);
				}
			}
			return;
		}

		if (CharacterSelects.IsValidIndex(0)) {

			GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, L_HitMouse);
			SendUnitTarget(L_HitMouse.Location, L_HitMouse.GetActor(), false,View);

			if (CountClick >= 2) {

				GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, L_HitMouse);
				SendUnitTarget(L_HitMouse.Location, L_HitMouse.GetActor(), true, View);
			}
		}
		return;
	}

	if (!IsSelectNull) {
		SetListSelectUnit(SelectUnit);
	}
	else {
		ClearListSelect();
	}
}

void ABasicPlayerController::DoubleClick() {
	
	CountClick = 0;
}

void ABasicPlayerController::SetListSelectUnit_Implementation(const TArray<AManAICharacter*>& NewList)
{
	if (CharacterSelects.IsValidIndex(0)) {
		for(AManAICharacter* ElementArray : CharacterSelects)
		{
			SendEnableSelect(ElementArray, false);
		}
		CharacterSelects.Empty();
	}

	for (AManAICharacter * ElementArray : NewList)
	{
		if (ElementArray->IsCommand(Command) && !ElementArray->IsUseVehicle && !ElementArray->IsDeath()) {
			SendEnableSelect(ElementArray, true);
			CharacterSelects.Add(ElementArray);
		}
	}
}

bool ABasicPlayerController::SetListSelectUnit_Validate(const TArray<AManAICharacter*>& NewList)
{
	return true;
}

void ABasicPlayerController::SendUnitTarget_Implementation(FVector Destination, AActor* ActorTarget, bool Run, bool StatusView)
{
	for(AManAICharacter * ElementArray : CharacterSelects) {
		
		if (!ElementArray->IsUseVehicle && !ElementArray->IsDeath()) {
			ElementArray->SetTarget(Destination, ActorTarget, Run);
			ElementArray->StatusView = StatusView;
		}
		else
		{
			SendEnableSelect(ElementArray, false);
		}
	}
}

bool ABasicPlayerController::SendUnitTarget_Validate(FVector Destination, AActor* ActorTarget, bool Run, bool StatusView)
{
	return true;
}

void ABasicPlayerController::ClearListSelect_Implementation()
{

	for(AManAICharacter * ElementArray : CharacterSelects)
	{
		SendEnableSelect(ElementArray, false);
	}
	CharacterSelects.Empty();
}

bool ABasicPlayerController::ClearListSelect_Validate()
{
	return true;
}

void ABasicPlayerController::SendEnableSelect_Implementation(AManAICharacter * Unit, bool NewEnable)
{
	Unit->SetSelectEnabled(NewEnable);
}

bool ABasicPlayerController::SendEnableSelect_Validate(AManAICharacter * Unit, bool NewEnable)
{
	return true;
}
