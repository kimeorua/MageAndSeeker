// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/CombatComponent.h"
#include "MonsterCombatComponent.generated.h"

class AEnemyWeapon;

UCLASS()
class MAGEANDSEEKER_API UMonsterCombatComponent : public UCombatComponent
{
	GENERATED_BODY()
public:
	virtual void RegisterWeapons_Implementation() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AEnemyWeapon* EnemyWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyWeapon> EnemyWeaponClass = nullptr;
};