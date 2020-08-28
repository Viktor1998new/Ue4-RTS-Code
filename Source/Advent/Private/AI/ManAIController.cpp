// Fill out your copyright notice in the Description page of Project Settings.


#include "ManAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Characters/ManAICharacter.h"

AManAIController::AManAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}

bool AManAIController::IsEnemy(ABasicAICharacter* PawnCharacter) {

	if (AManAICharacter * Man = Cast<AManAICharacter>(PawnCharacter)) {
		return !PawnMan->IsCommand(Man->GetCommand());
	}
	return false;
}

void AManAIController::AddEnemy(ABasicAICharacter* PawnCharacter)
{
	if (!PawnCharacter->IsDeath()) {

		if (Enemys.Find(PawnCharacter) == INDEX_NONE && IsEnemy(PawnCharacter)) {

			Enemys.Add(PawnCharacter);

			if (IsValid(Blackboard->GetValueAsObject(NameKeyActorTarget))) {

				if (AActor * CurrentTarget = Cast<AActor>(Blackboard->GetValueAsObject(NameKeyActorTarget))) {

					if (CurrentTarget != PawnCharacter) {

						if (PawnMan->GetDistanceTo(CurrentTarget) > PawnMan->GetDistanceTo(PawnCharacter))
						{
							Blackboard->SetValueAsObject(NameKeyActorTarget, PawnCharacter);
						}
					}
				}
			}
			else {
				Blackboard->SetValueAsObject(NameKeyActorTarget, PawnCharacter);
			}
		}
	}
}

ABasicAICharacter* AManAIController::FindEnemy()
{
	ABasicAICharacter* L_SelectEnemy = nullptr;

	UPawnSensingComponent* PawnSensung = (UPawnSensingComponent*)PawnMan->GetComponentByClass(UPawnSensingComponent::StaticClass());

	for (int i = 0; i < Enemys.Num(); i++)
	{

		if (IsValid(Enemys[i])) {

			if (Enemys[i]->IsDeath()) {

				Enemys.RemoveAt(i);
				i--;
				continue;
			}

			if (IsValid(PawnSensung)) {
				if (PawnMan->GetDistanceTo(Enemys[i]) > PawnSensung->LOSHearingThreshold) {
					
					Enemys.RemoveAt(i);
					i--;
					continue;
				}
			}

			if (!IsValid(L_SelectEnemy)) {

				L_SelectEnemy = Enemys[i];
			}
			else {

				if (PawnMan->GetDistanceTo(Enemys[i]) > PawnMan->GetDistanceTo(L_SelectEnemy)) {
					L_SelectEnemy = Enemys[i];
				}

			}
		}
		else {
			Enemys.RemoveAt(i);
			i--;
		}
	}

	return L_SelectEnemy;
}

void AManAIController::OnPossess(APawn* InPawn)
{
	PawnMan = Cast<AManAICharacter>(InPawn);
	Super::OnPossess(InPawn);
}
