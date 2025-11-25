// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/MonsterWeaponComponent.h"
#include "Props/Weapons/BaseWeapon.h"

void UMonsterWeaponComponent::RegisterWeapon(TArray<ABaseWeapon*> WeaponsToRegister)
{
	if (WeaponsToRegister.Num() > 1) { return; }

	EquipWeapon = WeaponsToRegister[0];
}

void UMonsterWeaponComponent::DestroyWeapon()
{
	if (IsValid(EquipWeapon))
	{
		EquipWeapon->Destroy();
	}	
}