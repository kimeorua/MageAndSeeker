// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/MageWeaponComponent.h"
#include "Props/Weapons/SkeletalWeapon.h"
#include "Props/Weapons/StaticWeapon.h"
#include "Subsystem/SaveLoadSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/EquipmentSubsystem.h"

#include"DebugHelper.h"

void UMageWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	FBookData FireBook, IceBook, LightningBook;
	FireBook.BookLevel = 1;
	FireBook.BookType = EBookType::Fire;
	EquipedBooks.Add(EBookType::Fire, FireBook);

	IceBook.BookLevel = 1;
	IceBook.BookType = EBookType::Ice;
	EquipedBooks.Add(EBookType::Ice, IceBook);

	LightningBook.BookLevel = 1;
	LightningBook.BookType = EBookType::Lightning;
	EquipedBooks.Add(EBookType::Lightning, LightningBook);

	if (USaveLoadSubsystem* SaveLoadSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<USaveLoadSubsystem>())
	{
		FBookData Data;

		Data = SaveLoadSubsystem->GetLoadedBookData(EBookType::Fire);
		EquipedBooks[EBookType::Fire] = Data;

		Data = SaveLoadSubsystem->GetLoadedBookData(EBookType::Ice);
		EquipedBooks[EBookType::Ice] = Data;

		Data = SaveLoadSubsystem->GetLoadedBookData(EBookType::Lightning);
		EquipedBooks[EBookType::Lightning] = Data;
	}

	CurrentBook = EquipedBooks.FindRef(EBookType::Fire);
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
			CurrentBook = EquipedBooks.FindOrAdd(EBookType::Fire);
		}
		break;
	case EBookType::Ice:
		if (EquipedBooks.Contains(EBookType::Ice))
		{
			CurrentBook = EquipedBooks.FindOrAdd(EBookType::Ice);
		}
		break;
	case EBookType::Lightning:
		if (EquipedBooks.Contains(EBookType::Lightning))
		{
			CurrentBook = EquipedBooks.FindOrAdd(EBookType::Lightning);
		}
		break;
	default:
		break;
	}
}

FVector UMageWeaponComponent::CalculatePosition()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	int32 ViewportX, ViewportY;
	PC->GetViewportSize(ViewportX, ViewportY);

	FVector2D CrosshairScreen(ViewportX * 0.5f, ViewportY * 0.5f);

	FVector WorldLocation, WorldDirection;
	PC->DeprojectScreenPositionToWorld(CrosshairScreen.X, CrosshairScreen.Y, WorldLocation, WorldDirection);

	FVector Start = WorldLocation;
	FVector End = Start + (WorldDirection * 10000.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwningCharacter_Base());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	FVector TargetPoint = bHit ? HitResult.Location : End;

	return TargetPoint;
}

FBookData UMageWeaponComponent::GetBookData(EBookType BookType)
{
	return EquipedBooks.FindRef(BookType);
}

void UMageWeaponComponent::ArtifactCreate()
{
	if (UEquipmentSubsystem* EquipmentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEquipmentSubsystem>())
	{
		Artifact = EquipmentSubsystem->CreateArtifact();
	}
}

void UMageWeaponComponent::ArtifactChange()
{
	if (UEquipmentSubsystem* EquipmentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEquipmentSubsystem>())
	{
		EquipmentSubsystem->ChangeArtifact(Artifact);
	}
}

void UMageWeaponComponent::ActivateArtifact()
{
	if (Artifact)
	{
		Artifact->OnActivate();
	}
}