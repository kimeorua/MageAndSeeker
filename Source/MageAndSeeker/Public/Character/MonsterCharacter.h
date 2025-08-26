// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "MonsterCharacter.generated.h"

class UMonsterAttributeSet;

UCLASS()
class MAGEANDSEEKER_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMonsterCharacter();

protected:
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

#pragma region AbilitySystem

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMonsterAttributeSet* MonsterAttributeSet;

#pragma endregion

};
