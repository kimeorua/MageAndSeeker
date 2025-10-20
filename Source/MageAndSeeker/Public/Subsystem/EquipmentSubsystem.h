// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Props/Artifact/BaseArtifact.h"
#include "EquipmentSubsystem.generated.h"



UCLASS(Abstract, Blueprintable)
class MAGEANDSEEKER_API UEquipmentSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	UBaseArtifact* CreateArtifact();

	UFUNCTION(BlueprintCallable)
	void ChangeArtifact(UBaseArtifact* EquipedArtifact);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Artifact DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* ArtifactDataTable = nullptr;

	TMap<int32, UBaseArtifact*>ArtifactInventory;
};
