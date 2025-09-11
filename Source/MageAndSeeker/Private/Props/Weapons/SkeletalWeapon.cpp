// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Weapons/SkeletalWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/Weapon/MageWeaponComponent.h"

ASkeletalWeapon::ASkeletalWeapon()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(WeaponMesh);
}