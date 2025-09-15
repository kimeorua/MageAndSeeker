// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Type/MageAndSeekerStruct.h"
#include "MageAndSeekerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UMageAndSeekerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 CurrentCycle = 1;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float HPLevel = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float AttackLevel = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<EBookType, FBookData> BookDatas;
};