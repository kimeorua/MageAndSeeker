// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Type/MageAndSeekerEnum.h"
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
	
protected:
	UMagicModule();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName ModuleID;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName ModuleName;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 UpgradeLevel;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EApplyPhase ApplyPhase;

public:
	virtual void Initialize(FName InID, EApplyPhase InPhase, FName InName, int32 InLevel = 1);
};
