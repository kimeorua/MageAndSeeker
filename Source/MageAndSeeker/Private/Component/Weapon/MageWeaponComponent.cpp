// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/MageWeaponComponent.h"
#include "Props/Weapons/SkeletalWeapon.h"
#include "Props/Weapons/StaticWeapon.h"

void UMageWeaponComponent::RegisterWeapon(TArray<ABaseWeapon*> WeaponsToRegister)
{
	for (ABaseWeapon* Weapon : WeaponsToRegister)
	{
		if (IsValid(Weapon))
		{
			EquipedWeapons.Add(Weapon->GetWeaponType(), Weapon);
		}
	}
}

AStaticWeapon* UMageWeaponComponent::GetStaff() const
{
	return Cast<AStaticWeapon>(EquipedWeapons.FindRef(EWeaponType::Staff));
}

ASkeletalWeapon* UMageWeaponComponent::GetBook() const
{
	return Cast<ASkeletalWeapon>(EquipedWeapons.FindRef(EWeaponType::Book));
}