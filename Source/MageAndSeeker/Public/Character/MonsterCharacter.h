// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "MonsterCharacter.generated.h"

class UMonsterAttributeSet;
class UMonsterCombatComponent;
class UMonsterUIComponent;

UCLASS()
class MAGEANDSEEKER_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AMonsterCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMonsterAttributeSet* MonsterAttributeSet;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UMonsterCombatComponent* MonsterCombatComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UMonsterUIComponent* MonsterUIComponent;

	virtual void InitCharacterStatAndAbility() override;
};