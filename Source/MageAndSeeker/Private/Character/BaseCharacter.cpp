// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GAS/MASAbilitySystemComponent.h"
#include "GAS/AttributeSet/MASBaseAttributeSet.h"

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

		DebugHelper::Print("Ability System And Base Attribute Set Is Ready");
	}
}