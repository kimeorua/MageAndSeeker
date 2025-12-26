// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/MageCombatComponent.h"

#include "Props/WeaponBase.h"
#include "Props/MagicBook.h"
#include "MageAndSeekerFunctionLibrary.h"
#include "SaveGame/MageAndSeekerSaveGame.h"
#include "Component/Rune/MageRuneComponent.h"

#include "DebugHelper.h"

UMageCombatComponent::UMageCombatComponent()
{
	MagicBookDatas.Empty();
}

void UMageCombatComponent::RegisterWeapons_Implementation()
{
	Staff = GetWorld()->SpawnActor<AWeaponBase>(StaffClass);
	MagicBook = GetWorld()->SpawnActor<AMagicBook>(MagicBookClass);

	if (Staff && MagicBook)
	{
		Staff->AttachToComponent(GetOwningCharacter_Base()->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, StaffSocket);
		MagicBook->AttachToComponent(GetOwningCharacter_Base()->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, MagicBookSocket);

		CurrentBookData = MagicBookDatas[EElementalType::Fire];
		MagicBook->BookMatterIntanceUpdatae(CurrentBookData.Type, CurrentBookData.BookLevel);
		UMageAndSeekerFunctionLibrary::AddGameplayTagToActorIfNone(GetOwner(), MageAndSeekerGameplayTag::Mage_Status_Book_Fire);
	}
}

void UMageCombatComponent::BookChange(EElementalType Type)
{
	if (IsValid(MagicBook))
	{
		CurrentBookData = MagicBookDatas[Type];
		MagicBook->PlayBookAnim();
		MagicBook->BookMatterIntanceUpdatae(Type, CurrentBookData.BookLevel);
	}
}

FBookData UMageCombatComponent::GetBookDataFromType(EElementalType Type) const
{
	if (MagicBookDatas.Contains(Type))
	{
		return MagicBookDatas[Type];
	}
	return FBookData();
}

void UMageCombatComponent::SaveData_Implementation(UMageAndSeekerSaveGame* SaveGame)
{
	if (MagicBookDatas.Contains(EElementalType::Fire))
	{
		SaveGame->BookLevelData.FireBookLevel = MagicBookDatas[EElementalType::Fire].BookLevel + 1;
	}

	if (MagicBookDatas.Contains(EElementalType::Ice))
	{
		SaveGame->BookLevelData.IceBookLevel = MagicBookDatas[EElementalType::Ice].BookLevel;
	}

	if (MagicBookDatas.Contains(EElementalType::Lightning))
	{
		SaveGame->BookLevelData.LightningBookLevel = MagicBookDatas[EElementalType::Lightning].BookLevel + 1;
	}
}

void UMageCombatComponent::LoadData_Implementation(const UMageAndSeekerSaveGame* SaveGame)
{
	FBookData SavedData;

	if (MagicBookDatas.Contains(EElementalType::Fire))
	{
		SavedData.Type = EElementalType::Fire;
		SavedData.BookLevel = SaveGame->BookLevelData.FireBookLevel;

		MagicBookDatas.Add(EElementalType::Fire, SavedData);
	}

	if (MagicBookDatas.Contains(EElementalType::Ice))
	{
		SavedData.Type = EElementalType::Ice;
		SavedData.BookLevel = SaveGame->BookLevelData.IceBookLevel;

		MagicBookDatas.Add(EElementalType::Ice, SavedData);
	}

	if (MagicBookDatas.Contains(EElementalType::Lightning))
	{
		SavedData.Type = EElementalType::Lightning;
		SavedData.BookLevel = SaveGame->BookLevelData.LightningBookLevel;

		MagicBookDatas.Add(EElementalType::Lightning, SavedData);
	}

	CurrentBookData = MagicBookDatas[EElementalType::Fire];

	if (IsValid(MagicBook))
	{
		MagicBook->BookMatterIntanceUpdatae(CurrentBookData.Type, CurrentBookData.BookLevel);
	}
}

void UMageCombatComponent::RuneEffectApply()
{
	if (!MageRuneComponent)
	{
		MageRuneComponent = GetOwner()->FindComponentByClass<UMageRuneComponent>();
	}

	ProjectileSpec.Count = 1;
	ProjectileSpec.CastSpeed = 1.0f;
	ProjectileSpec.ProjectileSpeed = 1500.0f;
	ProjectileSpec.Size = 1.0f;
	ProjectileSpec.HitEventTags.Reset();

	MageRuneComponent->RuneApply(CurrentBookData.Type, ProjectileSpec);
}

void UMageCombatComponent::SpawnProjectile()
{
	for (int32 i = 0; i < ProjectileSpec.Count; i++)
	{
		//TODO 투사체 스폰 하기
	}
}

void UMageCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	BookInit();
}

void UMageCombatComponent::BookInit()
{
	MagicBookDatas.Empty();

	for (uint8 i = (uint8)EElementalType::None + 1; i < (uint8)EElementalType::MAX; ++i)
	{
		EElementalType Type = static_cast<EElementalType>(i);

		FBookData TempData;
		TempData.BookLevel = 1;
		TempData.Type = Type;

		MagicBookDatas.Add(Type, TempData);
	}
}
