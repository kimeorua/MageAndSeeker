// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MonsterCharacter.h"
#include "GAS/AttributeSet/MonsterAttributeSet.h"
#include "Component/UI/MonsterUIComponent.h"
#include "Component/Weapon/MonsterWeaponComponent.h"
#include "Components/CapsuleComponent.h"

#include "DebugHelper.h"

#pragma region Basic

AMonsterCharacter::AMonsterCharacter()
{
	MonsterAttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("MonsterAttributeSet"));
	MonsterUIComponent = CreateDefaultSubobject<UMonsterUIComponent>(TEXT("Monster UI Component"));
	MonsterWeaponComponent = CreateDefaultSubobject<UMonsterWeaponComponent>(TEXT("Monster Weapon Component"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
}

void AMonsterCharacter::SettingElemental(EBookType Type)
{
    UMaterialInstanceDynamic* DynMat = GetMesh()->CreateDynamicMaterialInstance(0);
    if (!DynMat) return;

    FLinearColor Color;

    switch (Type)
    {
    case EBookType::Fire:
        Color = FLinearColor(1.f, 0.f, 0.f); 
        break;

    case EBookType::Ice:
        Color = FLinearColor(0.f, 0.5f, 1.f);
        break;

    case EBookType::Lightning:
        Color = FLinearColor(1.f, 1.f, 0.f);
        break;

    default:
        Color = FLinearColor::White;
        break;
    }
    DynMat->SetVectorParameterValue(TEXT("Elemental Color"), Color);
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