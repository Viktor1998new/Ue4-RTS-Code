// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPlayerPawn.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACameraPlayerPawn::ACameraPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	Arrow->SetupAttachment(DefaultSceneRoot);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(DefaultSceneRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);


}

// Called when the game starts or when spawned
void ACameraPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	ArmLenght = SpringArm->TargetArmLength;
}

void ACameraPlayerPawn::AddArmLenght(float Axis, float Speed)
{
	if (IsEnableMove) {
		ArmLenght = FMath::Max(ArmLenght - Axis * Speed, MinArmLenght);
	}
}

// Called every frame
void ACameraPlayerPawn::Tick(float DeltaTime)
{
	if (IsEnableMove) {
		if (IsRatation == false) {
			FVector2D Axis = CameraMove();
			FVector VectorAdd = FVector(Axis.Y, Axis.X, 0) * SpeedMove;
			AddActorLocalOffset(VectorAdd);
		}
	}
	
	Super::Tick(DeltaTime);
}

void ACameraPlayerPawn::SetEnableMove(bool NewEnable) {

	IsEnableMove = NewEnable;
}

FVector2D ACameraPlayerPawn::CameraMove() {

	if (IsValid(Player)) {

		float MouseX, MouseY;

		if (!Player->GetMousePosition(MouseX, MouseY)) {

			return FVector2D(0, 0);
		}
		int32 SizeX, SizeY;

		Player->GetViewportSize(SizeX, SizeY);

		return FVector2D(FMath::GetMappedRangeValueClamped(FVector2D(SizeX, SizeX - Radius), FVector2D(1, 0), MouseX) == 0 ? FMath::GetMappedRangeValueClamped(FVector2D(0, Radius), FVector2D(-1, 0), MouseX): FMath::GetMappedRangeValueClamped(FVector2D(SizeX, SizeX - Radius), FVector2D(1, 0), MouseX),
			FMath::GetMappedRangeValueClamped(FVector2D(SizeY, SizeY - Radius), FVector2D(-1, 0), MouseY) == 0 ? FMath::GetMappedRangeValueClamped(FVector2D(0, Radius), FVector2D(1, 0), MouseY) : FMath::GetMappedRangeValueClamped(FVector2D(SizeY, SizeY - Radius), FVector2D(-1, 0), MouseY));

	}

	return FVector2D(0, 0);
}