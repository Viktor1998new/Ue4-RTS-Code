// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class AManAICharacter;

/**
 * 
 */
UCLASS()
class ADVENT_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()

		int CountClick;

		FVector2D initalMousePosition;

		FTimerHandle UnusedHandle;

		bool View;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FLinearColor Command;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
		TArray<AManAICharacter*> CharacterSelects;

	UFUNCTION(BlueprintCallable)
		void SetCommand(FLinearColor NewCommand);


protected:
	virtual void SetupInputComponent() override;

	void OnLeftMouseButtonPressed();

	void OnLeftMouseButtonReleased();

	void OnViewButtonPressed();

	void OnViewButtonReleased();

	void DoubleClick();

	void OnRightMouseButtonPressed();

	void OnRightMouseButtonReleased();

	virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps)  const override;

	UFUNCTION(Server, Reliable, WithValidation)
		void SetListSelectUnit(const TArray<AManAICharacter*>& NewList);

		void SetListSelectUnit_Implementation(const TArray<AManAICharacter*>& NewList);

		bool SetListSelectUnit_Validate(const TArray<AManAICharacter*>& NewList);


	UFUNCTION(Server, Reliable, WithValidation)
		void SendUnitTarget(FVector Destination, AActor* ActorTarget, bool Run, bool StatusView);

		void SendUnitTarget_Implementation(FVector Destination, AActor* ActorTarget, bool Run, bool StatusView);

		bool SendUnitTarget_Validate(FVector Destination, AActor* ActorTarget, bool Run, bool StatusView);

		UFUNCTION(Server, Reliable, WithValidation)
			void ClearListSelect();

		void ClearListSelect_Implementation();

		bool ClearListSelect_Validate();

		UFUNCTION(Client, Reliable)
			void SendEnableSelect(AManAICharacter* Unit, bool NewEnable);

		void SendEnableSelect_Implementation(AManAICharacter* Unit, bool NewEnable);

		bool SendEnableSelect_Validate(AManAICharacter* Unit, bool NewEnable);
};
