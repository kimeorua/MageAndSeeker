// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Props/Artifact/BaseArtifact.h"
#include "Type/MageAndSeekerStruct.h"
#include "EquipmentSubsystem.generated.h"

#define GETTER(Type, Name) \
public: \
    FORCEINLINE Type Get##Name() const { return Name; }

UCLASS(Abstract, Blueprintable)
class MAGEANDSEEKER_API UEquipmentSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	UBaseArtifact* CreateArtifact();

	UBaseArtifact* CreateArtifact(int32 ID, FArtifactData Data);

	UFUNCTION(BlueprintCallable)
	void LoadAndCreateArtifact(int32 ID, FArtifactData Data);

	UFUNCTION(BlueprintCallable)
	UBaseArtifact* ChangeArtifact(int32 ChangeArtifactID, UBaseArtifact* OldArtifact);

	using FArtifactInventoryMap = TMap<int32, UBaseArtifact*>;
	GETTER(FArtifactInventoryMap, ArtifactInventory);

private:
	TMap<int32, UBaseArtifact*>ArtifactInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Artifacte", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<UBaseArtifact>>CreatableArtifacts;
};
