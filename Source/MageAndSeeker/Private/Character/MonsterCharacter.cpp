// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MonsterCharacter.h"
//------------------------ Component ------------------------//
#include "Component/Combat/MonsterCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/UI/MonsterUIComponent.h"
#include "Components/WidgetComponent.h"
//------------------------ Component ------------------------//

//------------------------ AttributeSet ------------------------//
#include "GAS/AttributeSet/MonsterAttributeSet.h"
//------------------------ AttributeSet ------------------------//

//------------------------ DataAsset ------------------------//
#include "DataAsset/StartUp/DataAsset_StartUp.h"
//------------------------ DataAsset ------------------------//

#include "UI/MonsterDebuffHUD.h"

AMonsterCharacter::AMonsterCharacter()
{
	MonsterAttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("MonsterAttributeSet"));
	MonsterCombatComponent = CreateDefaultSubobject<UMonsterCombatComponent>(TEXT("MonsterCombatComponent"));
	MonsterUIComponent = CreateDefaultSubobject<UMonsterUIComponent>(TEXT("MonsterUIComponent"));
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);

	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWigetComponent"));
	HPBarWidgetComponent->SetupAttachment(GetMesh());
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AMonsterCharacter::SettingMonsterColor(EDungeonElemental DungeonElemental)
{
	UMaterialInstanceDynamic* DynMat = GetMesh()->CreateDynamicMaterialInstance(0);

	if (!DynMat) return;

	FLinearColor Color;

	switch (DungeonElemental)
	{
	case EDungeonElemental::Fire:
		Color = FLinearColor(1.f, 0.14f, 0.f);
		break;

	case EDungeonElemental::Ice:
		Color = FLinearColor(0.0f, 0.27f, 1.f);
		break;

	case EDungeonElemental::Lightning:
		Color = FLinearColor(1.0f, 0.92f, 0.f);
		break;

	default:
		Color = FLinearColor::White;
		break;
	}
	DynMat->SetVectorParameterValue(TEXT("Elemental Color"), Color);
}

void AMonsterCharacter::OnCharacterDied()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
	MonsterCombatComponent->OnMonsterDied();
	MonsterUIComponent->UIHidden();
}

UAnimMontage* AMonsterCharacter::GetMonsterDiedAnimation() const
{
	return DieadMontage ? DieadMontage : nullptr;
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
	if (HPBarWidgetClass)
	{
		HPBarWidgetComponent->SetWidgetClass(HPBarWidgetClass);
		HPBarWidgetComponent->InitWidget();
	}
	UMonsterDebuffHUD* MonsterHUD = Cast<UMonsterDebuffHUD>(HPBarWidgetComponent->GetUserWidgetObject());

	if (MonsterHUD && MonsterUIComponent)
	{
		MonsterUIComponent->BindWidget(MonsterHUD);
	}

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUp* LodedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = MonsterLV;

			LodedData->GiveToAbilitySystemComponent(MASAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}
