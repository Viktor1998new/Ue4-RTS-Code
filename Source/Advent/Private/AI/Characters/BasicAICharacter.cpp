// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Characters/BasicAICharacter.h"

// Sets default values
ABasicAICharacter::ABasicAICharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABasicAICharacter::Attack(bool Active)
{
	ReceiveAttack(Active);
}

void ABasicAICharacter::SetEnableRun(bool Enable)
{
	ReceiveSetEnableRun(Enable);
}

bool ABasicAICharacter::IsDeath()
{
	return ReceiveIsDeath();
}
