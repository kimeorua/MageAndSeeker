// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseArtifact.generated.h"

#define GETTER(Type, Name) \
public: \
    FORCEINLINE Type Get##Name() const { return Name; }

#define SETTER(Type, Name) \
public: \
    FORCEINLINE void Set##Name(const Type& InValue) { Name = InValue; }

#define GETTER_SETTER(Type, Name) \
    GETTER(Type, Name) \
    SETTER(Type, Name)

UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class MAGEANDSEEKER_API UBaseArtifact : public UObject
{
	GENERATED_BODY()
	
private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact", meta = (AllowPrivateAccess = "true"))
    int32 ArtifactID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact", meta = (AllowPrivateAccess = "true"))
    int32 UpgradeLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact", meta = (AllowPrivateAccess = "true"))
    FText ArtifactName;

    GETTER_SETTER(int32, ArtifactID);
    GETTER_SETTER(int32, UpgradeLevel);
    GETTER_SETTER(FText, ArtifactName);

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "Artifact")
    void OnActivate();
};
