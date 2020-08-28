// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacteristicComponent.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include  "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCharacteristicComponent::UCharacteristicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	// ...
}

void UCharacteristicComponent::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps)  const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacteristicComponent, Health);
	DOREPLIFETIME(UCharacteristicComponent, Endurance);

	//Max Value
	DOREPLIFETIME(UCharacteristicComponent, MaxHealth);
	DOREPLIFETIME(UCharacteristicComponent, MaxEndurance);
}

void UCharacteristicComponent::CalculateHealth(float Value)
{
	if (GIsServer) {
		if (!IsDead) {
			Health = FMath::Clamp<float>(Health + Value, 0, MaxHealth);
			if (Health == 0) {
				OnDeath.Broadcast();
				IsDead = true;
			}
		}
	}
}

void UCharacteristicComponent::CalculateEndurance(float Value)
{
	if (GIsServer) {
		Endurance = FMath::Clamp<float>(Endurance + Value, 0, MaxEndurance);
		if (Endurance == 0) {
			EnduranceEnd.Broadcast();
		}
	}
}

void UCharacteristicComponent::SetStaticEndurance(FName NewStatic)
{
	if (GIsServer) {

		if(SpeedEndurance.Contains(NewStatic)){
		StaticEndurance = NewStatic; 
		}
		else {
			StaticEndurance = "Default";
		}

		if (!GetWorld()->GetTimerManager().IsTimerActive(EnduranceTimer)) {
			GetWorld()->GetTimerManager().SetTimer(EnduranceTimer, this, &UCharacteristicComponent::TickEndurance, 0.5f, true);
		}
		else {
			GetWorld()->GetTimerManager().ClearTimer(EnduranceTimer);
			GetWorld()->GetTimerManager().SetTimer(EnduranceTimer, this, &UCharacteristicComponent::TickEndurance, 0.5f, true);
		}
	}
}

void UCharacteristicComponent::BeginPlay() {

	if (GIsServer) {
		
		if (!GetWorld()->GetTimerManager().IsTimerActive(EnduranceTimer))
			GetWorld()->GetTimerManager().SetTimer(EnduranceTimer, this, &UCharacteristicComponent::TickEndurance, 0.5f, true);
	}
}

void UCharacteristicComponent::TickEndurance() {

	CalculateEndurance(SpeedEndurance[StaticEndurance] * 0.5f);

	if (Endurance == MaxEndurance|| Endurance == 0)
		GetWorld()->GetTimerManager().ClearTimer(EnduranceTimer);
}

void UCharacteristicComponent::TickHealth() {

	CalculateHealth(SpeedHealth * -0.5f);

	if (Health == 0)
		GetWorld()->GetTimerManager().ClearTimer(HealthTimer);
}

bool UCharacteristicComponent::UseConsumingItem(TSubclassOf<AConsumingItem> Class) {

	CalculateEndurance(Class->GetDefaultObject<AConsumingItem>()->CalculateEndurance);

	CalculateHealth(Class->GetDefaultObject<AConsumingItem>()->CalculateHealth);
			
	return true;
}