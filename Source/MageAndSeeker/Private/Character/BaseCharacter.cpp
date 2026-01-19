// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"

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

void ABaseCharacter::OnCharacterDied()
{

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetMapName().Contains("DevMap"))
	{
		InitCharacterStatAndAbility();
	}
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (MASAbilitySystemComponent && MASBaseAttributeSet)
	{
		MASAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ABaseCharacter::InitCharacterStatAndAbility()
{
}