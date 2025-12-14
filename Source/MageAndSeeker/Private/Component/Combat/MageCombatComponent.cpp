// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/MageCombatComponent.h"

#include "Props/WeaponBase.h"
#include "Props/MagicBook.h"
#include "MageAndSeekerFunctionLibrary.h"

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
		MagicBook->PlayBookAnim();
		MagicBook->BookMatterIntanceUpdatae(Type, CurrentBookData.BookLevel);
		CurrentBookData = MagicBookDatas[Type];
	}
}

void UMageCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	BookInit();
	//TODO : Save파일에서 정보 받아 초기화 하기.
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
