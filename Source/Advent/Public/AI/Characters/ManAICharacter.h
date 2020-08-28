#pragma once
#include "CoreMinimal.h"
#include "AI/Characters/BasicAICharacter.h"
#include "ManAICharacter.generated.h"

class ABasicPlayerController;
class UInventoryComponent;
class UClothesComponent;
class UCharacteristicComponent;
class AManAIController;

UENUM(BlueprintType)
enum class EPriorities : uint8 {

	P_None 	UMETA(DisplayName = "None"),
	P_Attack UMETA(DisplayName = "Attack"),
	P_Defense UMETA(DisplayName = "Defense"),
	P_support UMETA(DisplayName = "Support")
};

/**
 * 
 */
UCLASS(abstract)
class ADVENT_API AManAICharacter : public ABasicAICharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = Components, BlueprintReadOnly, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		UInventoryComponent* InventoryComponent;

	UPROPERTY(Category = Components, BlueprintReadOnly, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		UClothesComponent* ClothesComponent;

	UPROPERTY(Category = Components, BlueprintReadOnly, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		UCharacteristicComponent* CharacteristicComponent;

	UPROPERTY(EditInstanceOnly, Category = "Default")
		FLinearColor Command;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UTexture2D * Image;

	bool IsUseVehicle;

	bool StatusView;


public:
	// Sets default values for this character's properties
	AManAICharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintPure)
		EPriorities GetPriorities();

	UFUNCTION(BlueprintCallable)
	void SetPriorities(EPriorities NewPriorities);

	UFUNCTION(BlueprintPure)
		bool IsStatusView() const {
			return StatusView;
		};


	UFUNCTION(BlueprintPure)
		bool IsCommand(FLinearColor Verifiable);

	UFUNCTION(BlueprintCallable)
		virtual void SetCommand(ABasicPlayerController * PlayerController,bool AI);

	UFUNCTION(BlueprintCallable)
		virtual void SetSelectEnabled(bool NewEnable);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SelectEnable"))
		void ReceiveSelectEnabled(bool NewEnable);

	UFUNCTION(BlueprintCallable)
		virtual void SetTarget(FVector Destination, AActor* ActorTarget, bool Run);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SetTarget"))
		void ReceiveSetTarget(FVector Destination, AActor* ActorTarget, bool Run);


	UFUNCTION(BlueprintPure)
		FLinearColor GetCommand() const {
		return Command;
	};
};
