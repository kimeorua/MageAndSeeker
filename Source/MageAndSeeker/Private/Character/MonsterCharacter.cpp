// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MonsterCharacter.h"
#include "GAS/AttributeSet/MonsterAttributeSet.h"
#include "Component/UI/MonsterUIComponent.h"

AMonsterCharacter::AMonsterCharacter()
{
	MonsterAttributeSet = CreateDefaultSubobject<UMonsterAttributeSet>(TEXT("MonsterAttributeSet"));
	MonsterUIComponent = CreateDefaultSubobject<UMonsterUIComponent>(TEXT("Monster UI Component"));
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

UPawnUIComponent* AMonsterCharacter::GetPawnUIComponent() const
{
	return MonsterUIComponent;
}

UMonsterUIComponent* AMonsterCharacter::GetMonsterUIComponent() const
{
	return MonsterUIComponent;
}