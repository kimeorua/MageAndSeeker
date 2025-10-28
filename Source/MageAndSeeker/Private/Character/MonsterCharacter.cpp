// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MonsterCharacter.h"
#include "GAS/AttributeSet/MonsterAttributeSet.h"
#include "Component/UI/MonsterUIComponent.h"
#include "Component/Weapon/MonsterWeaponComponent.h"
#include "Components/CapsuleComponent.h"

#pragma region Basic

AMonsterCharacter::AMonsterCharacter()
{
	MonsterAttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("MonsterAttributeSet"));
	MonsterUIComponent = CreateDefaultSubobject<UMonsterUIComponent>(TEXT("Monster UI Component"));
	MonsterWeaponComponent = CreateDefaultSubobject<UMonsterWeaponComponent>(TEXT("Monster Weapon Component"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

#pragma endregion

#pragma region DIP

UPawnUIComponent* AMonsterCharacter::GetPawnUIComponent() const
{
	return MonsterUIComponent;
}

UMonsterUIComponent* AMonsterCharacter::GetMonsterUIComponent() const
{
	return MonsterUIComponent;
}

UPawnWeaponComponent* AMonsterCharacter::GetPawnWeaponComponent() const
{
	return MonsterWeaponComponent;
}

UMonsterWeaponComponent* AMonsterCharacter::GetMonsterWeaponComponent() const
{
	return MonsterWeaponComponent;
}

#pragma endregion