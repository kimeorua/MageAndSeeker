// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Type/MageAndSeekerStruct.h"
#include "MagicModule.generated.h"

#define GETTER(Type, Name) \
public: \
    FORCEINLINE Type Get##Name() const { return Name; }

#define SETTER(Type, Name) \
public: \
    FORCEINLINE void Set##Name(const Type& InValue) { Name = InValue; }

#define GETTER_SETTER(Type, Name) \
    GETTER(Type, Name) \
    SETTER(Type, Name)

UCLASS(Blueprintable)
class MAGEANDSEEKER_API UMagicModule : public UObject
{
	GENERATED_BODY()
	
public:
	GETTER_SETTER(FName, ModuleID);
	GETTER_SETTER(int32, UpgradeLevel);
	GETTER_SETTER(EApplyPhase, ApplyPhase);

protected:
	UMagicModule();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName ModuleID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 UpgradeLevel;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EApplyPhase ApplyPhase;

public:
	virtual void Initialize(FName InID, EApplyPhase InPhase, int32 InLevel = 1);

	UFUNCTION(BlueprintImplementableEvent)
	FMagicOrbSpawnData ActivateModule(FMagicOrbSpawnData Data);

	void ModuleActivate(FMagicOrbSpawnData& Data);
};