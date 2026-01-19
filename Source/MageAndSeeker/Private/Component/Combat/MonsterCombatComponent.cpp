// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/MonsterCombatComponent.h"
#include "Props/EnemyWeapon.h"

void UMonsterCombatComponent::RegisterWeapons_Implementation()
{
	EnemyWeapon = GetWorld()->SpawnActor<AEnemyWeapon>(EnemyWeaponClass);

	if (EnemyWeapon)
	{
		EnemyWeapon->AttachToComponent(GetOwningCharacter_Base()->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");
	}
}

void UMonsterCombatComponent::OnMonsterDied()
{
	if (IsValid(EnemyWeapon))
	{
		EnemyWeapon->Destroy();
	}
}
