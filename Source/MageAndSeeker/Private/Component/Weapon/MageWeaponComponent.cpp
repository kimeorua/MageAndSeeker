// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/MageWeaponComponent.h"
#include "Props/Weapons/SkeletalWeapon.h"
#include "Props/Weapons/StaticWeapon.h"

void UMageWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentBook.BookLevel = EquipedBooks.FindRef(EBookType::Fire).BookLevel;
	CurrentBook.BookType = EquipedBooks.FindRef(EBookType::Fire).BookType;
}

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

void UMageWeaponComponent::SettingCurrentBook(EBookType BookType)
{
	switch (BookType)
	{
	case EBookType::Fire:
		if (EquipedBooks.Contains(EBookType::Fire))
		{
			CurrentBook = EquipedBooks.FindRef(EBookType::Fire);
		}
		break;
	case EBookType::Ice:
		if (EquipedBooks.Contains(EBookType::Ice))
		{
			CurrentBook = EquipedBooks.FindRef(EBookType::Ice);
		}
		break;
	case EBookType::Lightning:
		if (EquipedBooks.Contains(EBookType::Lightning))
		{
			CurrentBook = EquipedBooks.FindRef(EBookType::Lightning);
		}
		break;
	default:
		break;
	}
}