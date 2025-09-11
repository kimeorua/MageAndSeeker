// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "MonsterCharacter.generated.h"

class UMonsterAttributeSet;
class UMonsterUIComponent;
class UMonsterWeaponComponent;

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

	// ~ Begin IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UMonsterUIComponent* GetMonsterUIComponent() const override;
	// ~ End IPawnUIInterface

	// ~ Begin IPawnUIInterface
	virtual UPawnWeaponComponent* GetPawnWeaponComponent() const override;
	virtual UMonsterWeaponComponent* GetMonsterWeaponComponent() const override;
	// ~ End IPawnUIInterface

#pragma region AbilitySystem

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UMonsterAttributeSet* MonsterAttributeSet;

#pragma endregion

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Component", meta = (AllowPrivateAccess = "true"))
	UMonsterUIComponent* MonsterUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Component", meta = (AllowPrivateAccess = "true"))
	UMonsterWeaponComponent* MonsterWeaponComponent;

#pragma endregion

};
