// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPlayerController.h"
#include "GamePlay/BasicHUD.h"
#include "GameFramework/Pawn.h"
#include "InterfaceSelectPawn.h"
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
	CountClick++;

	if (!GetWorldTimerManager().IsTimerActive(UnusedHandle))
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABasicPlayerController::DoubleClick, 0.50f, false);

}

void ABasicPlayerController::OnRightMouseButtonReleased() {

	ACameraPlayerPawn* L_CameraPawn = Cast<ACameraPlayerPawn>(GetPawn());

	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);

	if (IsValid(L_CameraPawn)) {
		L_CameraPawn->IsRatation = false;
	}

	if (initalMousePosition == MousePosition) {
		
		FHitResult L_HitMouse;

		if (CharacterSelects.IsValidIndex(0)) {

			bool Run = CountClick >= 2;
			GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, L_HitMouse);
			SendUnitTarget(L_HitMouse.Location, L_HitMouse.GetActor(), Run, View);
		}
	}
}

void ABasicPlayerController::OnLeftMouseButtonPressed() {

	ClearListSelect();
	
	GetMousePosition(initalMousePosition.X, initalMousePosition.Y);
	Cast<ABasicHUD>(GetHUD())->SelectEnable();

}

void ABasicPlayerController::OnLeftMouseButtonReleased() {

	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);

	bool IsSelectNull;
	TArray<APawn*> SelectUnit;
	FHitResult L_HitMouse;
	Cast<ABasicHUD>(GetHUD())->SelectDisable(IsSelectNull, SelectUnit);

	if (FVector2D(initalMousePosition - MousePosition).Size()<5)
	{
		GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, L_HitMouse);
		
		APawn* HitPawn = Cast<APawn>(L_HitMouse.GetActor());

		if (IsValid(HitPawn)) {

			ClearListSelect();
			TArray<APawn*> NewSelectUnit;
			NewSelectUnit.Add(HitPawn);
			SetListSelectUnit(NewSelectUnit);
			return;
		}
	}

	if (!IsSelectNull) {
		SetListSelectUnit(SelectUnit);
	}
}

void ABasicPlayerController::DoubleClick() {
	
	CountClick = 0;
}

void ABasicPlayerController::SetListSelectUnit_Implementation(const TArray<APawn*>& NewList)
{

	if (CharacterSelects.IsValidIndex(0)) {
		for(APawn* ElementArray : CharacterSelects)
		{
			SendEnableSelect(ElementArray, false);
		}
		CharacterSelects.Empty();
	}

	for (APawn* ElementArray : NewList)
	{
		if (IInterfaceSelectPawn::Execute_IsCommand(ElementArray,Command) && !IInterfaceSelectPawn::Execute_IsUseVehicle(ElementArray) && !IInterfaceSelectPawn::Execute_IsDeath(ElementArray)) {
			SendEnableSelect(ElementArray, true);
			CharacterSelects.Add(ElementArray);
		}
	}
}

bool ABasicPlayerController::SetListSelectUnit_Validate(const TArray<APawn*>& NewList)
{
	return true;
}

void ABasicPlayerController::SendUnitTarget_Implementation(FVector Destination, AActor* ActorTarget, bool Run, bool StatusView)
{
	for(APawn* ElementArray : CharacterSelects) {
		
		if (!IInterfaceSelectPawn::Execute_IsUseVehicle(ElementArray) && !IInterfaceSelectPawn::Execute_IsDeath(ElementArray)) {
			IInterfaceSelectPawn::Execute_SetTarget(ElementArray,Destination, ActorTarget, Run);
			//Cast<IInterfaceSelectPawn>(ElementArray)->StatusView = StatusView;
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

	for(APawn* ElementArray : CharacterSelects)
	{
		SendEnableSelect(ElementArray, false);
	}
	CharacterSelects.Empty();
}

bool ABasicPlayerController::ClearListSelect_Validate()
{
	return true;
}

void ABasicPlayerController::SendEnableSelect_Implementation(APawn* Unit, bool NewEnable)
{
	IInterfaceSelectPawn::Execute_SetSelectEnabled(Unit,NewEnable);
}

bool ABasicPlayerController::SendEnableSelect_Validate(APawn* Unit, bool NewEnable)
{
	return true;
}
