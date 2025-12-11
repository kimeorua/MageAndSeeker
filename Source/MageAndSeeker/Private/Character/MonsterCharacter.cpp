// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MonsterCharacter.h"
//------------------------ Component ------------------------//
#include "Component/Combat/MonsterCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/UI/MonsterUIComponent.h"
//------------------------ Component ------------------------//

//------------------------ AttributeSet ------------------------//
#include "GAS/AttributeSet/MonsterAttributeSet.h"
//------------------------ AttributeSet ------------------------//

//------------------------ DataAsset ------------------------//
#include "DataAsset/StartUp/DataAsset_StartUp.h"
//------------------------ DataAsset ------------------------//

AMonsterCharacter::AMonsterCharacter()
{
	MonsterAttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("MonsterAttributeSet"));
	MonsterCombatComponent = CreateDefaultSubobject<UMonsterCombatComponent>(TEXT("MonsterCombatComponent"));
	MonsterUIComponent = CreateDefaultSubobject<UMonsterUIComponent>(TEXT("MonsterUIComponent"));
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

void AMonsterCharacter::InitCharacterStatAndAbility()
{
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUp* LodedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;

			//TODO: 던전 생성시 선택한 몬스터 레벨에 따라, Ablity 및 AttributeSet LV 설정!

			LodedData->GiveToAbilitySystemComponent(MASAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}
