// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "CameraPlayerPawn.generated.h"

UCLASS()
class ADVENT_API ACameraPlayerPawn : public APawn
{
	GENERATED_BODY()


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PawnCamera)
		float Radius = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PawnCamera)
		float SpeedMove = 30;

	UPROPERTY(EditDefaultsOnly, Category = PawnCamera)
	float MinArmLenght;

	UPROPERTY(BlueprintReadOnly)
	float ArmLenght;

	UPROPERTY(BlueprintReadOnly)
	bool IsEnableMove = true;

	UPROPERTY(BlueprintReadOnly, Category = Camera)
		bool IsRatation;

	UPROPERTY(BlueprintReadWrite, Category = "PawnCamera", meta = (ExposeOnSpawn = "true"))
		APlayerController* Player;

protected:

	UPROPERTY(Category = Components, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(Category = Components, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		UArrowComponent * Arrow;

	UPROPERTY(Category = Components, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent * SpringArm;

	UPROPERTY(Category = Components, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent * Camera;

	// Sets default values for this pawn's properties
	ACameraPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	UFUNCTION(BlueprintCallable)
		void SetEnableMove(bool NewEnable);

	UFUNCTION(BlueprintCallable)
		void AddArmLenght(float Axis, float Speed);

	virtual void Tick(float DeltaTime) override;

	FVector2D CameraMove();

};
