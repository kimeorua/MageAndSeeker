// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MonsterCharacter.h"
#include "BossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API ABossCharacter : public AMonsterCharacter
{
	GENERATED_BODY()
	
protected:
	// ~ Begin IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UMonsterUIComponent* GetMonsterUIComponent() const override;
	// ~ End IPawnUIInterface
};
