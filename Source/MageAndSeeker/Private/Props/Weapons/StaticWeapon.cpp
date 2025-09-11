// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Weapons/StaticWeapon.h"
#include "Components/StaticMeshComponent.h"

AStaticWeapon::AStaticWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(WeaponMesh);
}