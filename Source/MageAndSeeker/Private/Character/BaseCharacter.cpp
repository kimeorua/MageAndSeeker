// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"
#include "DataAsset/StartUp/DataAsset_StartUp.h"

#include "DebugHelper.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MASAbilitySystemComponent = CreateDefaultSubobject<UMASAbilitySystemComponent>(TEXT("MASAbilitySystemComponent"));
	MASBaseAttributeSet = CreateDefaultSubobject<UMASBaseAttributeSet>(TEXT("MASBaseAttributeSet"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetMASAbilitySystemComponent();
}

void ABaseCharacter::InitCharacterStatAndAbility()
{
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUp* LodedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;
			CreateUIAndAdd();
			LodedData->GiveToAbilitySystemComponent(MASAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}

void ABaseCharacter::CharacterDied()
{
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (MASAbilitySystemComponent && MASBaseAttributeSet)
	{
		MASAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UPawnUIComponent* ABaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

UPawnWeaponComponent* ABaseCharacter::GetPawnWeaponComponent() const
{
	return nullptr;
}

void ABaseCharacter::CreateUIAndAdd()
{
}
