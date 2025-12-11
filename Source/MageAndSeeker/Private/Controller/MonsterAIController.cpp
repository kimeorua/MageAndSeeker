// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MonsterAIController.h"

AMonsterAIController::AMonsterAIController(const FObjectInitializer& ObjectInitializer)
{
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AMonsterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
}