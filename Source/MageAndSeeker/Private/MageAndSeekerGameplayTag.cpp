// Fill out your copyright notice in the Description page of Project Settings.


#include "MageAndSeekerGameplayTag.h"

namespace MageAndSeekerGameplayTag
{
	/* Input Tag */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, "InputTag.Attack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Artifact, "InputTag.Artifact");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction, "InputTag.Interaction");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_BookChange_Fire, "InputTag.BookChange.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_BookChange_Ice, "InputTag.BookChange.Ice");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_BookChange_Lightning, "InputTag.BookChange.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ManaRecharge, "InputTag.ManaRecharge");

	/*Mage Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_Book_Fire, "Mage.Status.Book.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_Book_Ice, "Mage.Status.Book.Ice");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_Book_Lightning, "Mage.Status.Book.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_CombatMode, "Mage.Status.CombatMode");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_ManaFull, "Mage.Status.ManaFull");

	UE_DEFINE_GAMEPLAY_TAG(Mage_Ability_BookChange, "Mage.Ability.BookChange");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Ability_Attack, "Mage.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Ability_Interaction, "Mage.Ability.Interaction");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Ability_ManaRecovery, "Mage.Ability.ManaRecovery");

	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_ActivateBookChangeEffect, "Mage.Event.ActivateBookChangeEffect");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_SpawnProjectile, "Mage.Event.SpawnProjectile");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_ModeChange, "Mage.Event.ModeChange");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_APCharge, "Mage.Event.APCharge");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_InteractionEnd, "Mage.Event.InteractionEnd");

	UE_DEFINE_GAMEPLAY_TAG(Mage_Data_APChargePer, "Mage.Data.APChargePer");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Data_ManaCost, "Mage.Data.ManaCost");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Data_ManaRecoveyTime, "Mage.Data.ManaRecoveyTime");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Data_ManaRecoveyAmount, "Mage.Data.ManaRecoveyAmount");

	/*Shared Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_TakeDamage, "Shared.Ability.TakeDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_TakeDamage, "Shared.Event.TakeDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Data_Damage, "Shared.Data.TakeDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_DamageType_Fire, "Shared.DamageType.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Shared_DamageType_Ice, "Shared.DamageType.Ice");
	UE_DEFINE_GAMEPLAY_TAG(Shared_DamageType_Lightning, "Shared.DamageType.Lightning");
}