// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/EquipmentSubsystem.h"
#include "Type/MageAndSeekerStruct.h"

#include "DebugHelper.h"


void UEquipmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("UEquipmentSubsystem Init");
}

void UEquipmentSubsystem::Deinitialize()
{
}

UBaseArtifact* UEquipmentSubsystem::CreateArtifact()
{
	if (!ArtifactDataTable) { return nullptr; }

	UBaseArtifact* ReturnArtifact = nullptr;

	 int32 RandomIndex = FMath::RandRange(0, ArtifactDataTable->GetRowMap().Num() - 1);

	 FString IndexString = FString::FromInt(RandomIndex);
	 FString CombinedString = FString("Artifact") + IndexString;

	const FName RowName = FName(*(FString("Artifact") + FString::FromInt(RandomIndex)));
	const FArtifactDataRow* Row = ArtifactDataTable->FindRow<FArtifactDataRow>(RowName, TEXT(""));

	if (!Row || !Row->ArtifactClass) { return nullptr; }

	if (ArtifactInventory.Contains(RandomIndex))
	{
		DebugHelper::Print("Call Artifact");
		int32 NewLevel = ArtifactInventory[RandomIndex]->GetUpgradeLevel() + 1;
		ArtifactInventory[RandomIndex]->SetUpgradeLevel(NewLevel);

		DebugHelper::Print("Artifact Level is", NewLevel);
		return ArtifactInventory[RandomIndex];
	}
	else
	{
		ReturnArtifact = NewObject<UBaseArtifact>(this, Row->ArtifactClass);
		ReturnArtifact->SetArtifactID(Row->ArtifactID);
		ReturnArtifact->SetArtifactName(Row->ArtifactName);
		ReturnArtifact->SetUpgradeLevel(1);

		DebugHelper::Print("Create New Artifact");
	}

	return ReturnArtifact;
}

void UEquipmentSubsystem::ChangeArtifact(UBaseArtifact* EquipedArtifact)
{
	if (EquipedArtifact)
	{
		ArtifactInventory.Add(EquipedArtifact->GetArtifactID(), EquipedArtifact);
	}
	else
	{
		DebugHelper::Print("Artifact Is Not Vaild");
	}
}