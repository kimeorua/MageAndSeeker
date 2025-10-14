// Fill out your copyright notice in the Description page of Project Settings.


#include "MageAndSeekerGameplayTag.h"

namespace MageAndSeekerGameplayTag
{
	/* Input Tag */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interection, "InputTag.Interection");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, "InputTag.Attack");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_BookChange_Fire, "InputTag.BookChange.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_BookChange_Ice, "InputTag.BookChange.Ice");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_BookChange_Lightning, "InputTag.BookChange.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ManaRecharge, "InputTag.ManaRecharge");

	/*Mage Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_Book_Fire, "Mage.Status.Book.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_Book_Ice, "Mage.Status.Book.Ice");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_Book_Lightning, "Mage.Status.Book.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_CombatMode, "Mage.Status.CombatMode");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Status_ManaRecharging, "Mage.Status.ManaRecharging");

	UE_DEFINE_GAMEPLAY_TAG(Mage_Ability_BookChange, "Mage.Ability.BookChange");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Ability_Attack, "Mage.Ability.Attack");

	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_ActivateBookChangeEffect, "Mage.Event.ActivateBookChangeEffect");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_SpawnProjectile , "Mage.Event.SpawnProjectile");
	UE_DEFINE_GAMEPLAY_TAG(Mage_Event_ModeChange, "Mage.Event.ModeChange");

	UE_DEFINE_GAMEPLAY_TAG(Mage_Data_ManaChargePer, "Mage.Data.ManaChargePer");
}