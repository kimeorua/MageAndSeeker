// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Weapon/PawnWeaponComponent.h"
#include "MonsterWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API UMonsterWeaponComponent : public UPawnWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void RegisterWeapon(TArray<ABaseWeapon*>WeaponsToRegister) override;

	UFUNCTION(BlueprintCallable)
	void DestroyWeapon();

private:
	ABaseWeapon* EquipWeapon;
};
