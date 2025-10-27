// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/EquipmentSubsystem.h"
#include "Type/MageAndSeekerStruct.h"
#include "Props/Module/MagicModule.h"

#include "DebugHelper.h"


void UEquipmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("UEquipmentSubsystem Init");

	CreateAllModule();
}

void UEquipmentSubsystem::Deinitialize()
{
}

UBaseArtifact* UEquipmentSubsystem::CreateArtifact()
{
	UBaseArtifact* NewArtifact = nullptr;

	if (CreatableArtifacts.Num() == 0)
	{
		return nullptr;
	}

	TArray<int32> Keys;
	CreatableArtifacts.GetKeys(Keys);

	int32 RandomKeyIndex = FMath::RandRange(0, Keys.Num() - 1);
	int32 SelectedKey = Keys[RandomKeyIndex];

	TSubclassOf<UBaseArtifact> ArtifactClass = CreatableArtifacts.FindRef(SelectedKey);

	if (ArtifactClass)
	{
		NewArtifact = NewObject<UBaseArtifact>(this, ArtifactClass);
		CreatableArtifacts.Remove(SelectedKey);
		ArtifactInventory.Add(NewArtifact->GetArtifactID(), NewArtifact);
	}

	return NewArtifact;
}

UBaseArtifact* UEquipmentSubsystem::CreateArtifact(int32 ID, FArtifactData Data)
{
	UBaseArtifact* NewArtifact = nullptr;

	if (ID < 0) { return nullptr; }

	TSubclassOf<UBaseArtifact> ArtifactClass = CreatableArtifacts.FindRef(ID);

	if (ArtifactClass)
	{
		NewArtifact = NewObject<UBaseArtifact>(this, ArtifactClass);
		NewArtifact->SetArtifactID(Data.ArtifactID);
		NewArtifact->SetArtifactName(Data.ArtifactName);
		NewArtifact->SetUpgradeLevel(Data.UpgradeLevel);
	}

	return NewArtifact;
}

void UEquipmentSubsystem::LoadAndCreateArtifact(int32 ID, FArtifactData Data)
{
	ArtifactInventory.Empty();

	TSubclassOf<UBaseArtifact> ArtifactClass = CreatableArtifacts.FindRef(ID);

	if (ArtifactClass)
	{
		UBaseArtifact* NewArtifact = NewObject<UBaseArtifact>(this, ArtifactClass);
		CreatableArtifacts.Remove(ID);

		NewArtifact->SetArtifactID(Data.ArtifactID);
		NewArtifact->SetArtifactName(Data.ArtifactName);
		NewArtifact->SetUpgradeLevel(Data.UpgradeLevel);

		ArtifactInventory.Add(NewArtifact->GetArtifactID(), NewArtifact);
	}
}

UBaseArtifact* UEquipmentSubsystem::ChangeArtifact(int32 ChangeArtifactID, UBaseArtifact* OldArtifact)
{
	if (ArtifactInventory.Contains(ChangeArtifactID))
	{
		ArtifactInventory.Add(OldArtifact->GetArtifactID(), OldArtifact);

		return ArtifactInventory[ChangeArtifactID];
	}
	return nullptr;
}

void UEquipmentSubsystem::CreateAllModule()
{
	if (!ModuleDataTable) { return;}

	AllModules.Empty();

	static const FString ContextString(TEXT("CreateAllModule"));
	TArray<FMagicModuleDataTableRow*> AllRows;
	ModuleDataTable->GetAllRows(ContextString, AllRows);

	for (FMagicModuleDataTableRow* Row : AllRows)
	{
		if (!Row->MagicModuleClass) { continue; }

		UMagicModule* NewModule = NewObject<UMagicModule>(this, Row->MagicModuleClass);
		NewModule->Initialize(Row->ModuleID, Row->ApplyPhase);

		AllModules.Add(Row->ModuleID, NewModule);
	}
}
