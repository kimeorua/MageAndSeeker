// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Type/Structs/SaveDataStructs.h"
#include "MageAndSeekerSaveGame.generated.h"

class UBaseArtifact;

UCLASS()
class MAGEANDSEEKER_API UMageAndSeekerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FStatSaveData MageStat;

	UPROPERTY()
	FBookLevelData BookLevelData;
};