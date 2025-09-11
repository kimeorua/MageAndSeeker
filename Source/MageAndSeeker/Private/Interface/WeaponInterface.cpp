// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/WeaponInterface.h"

// Add default functionality here for any IWeaponInterface functions that are not pure virtual.

UMageWeaponComponent* IWeaponInterface::GetMageWeaponComponent() const
{
	return nullptr;
}

UMonsterWeaponComponent* IWeaponInterface::GetMonsterWeaponComponent() const
{
	return nullptr;
}
