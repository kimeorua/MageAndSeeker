// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/MageUIComponent.h"

void UMageUIComponent::ChangeBookUI(EBookType BookType)
{
	OnChangeBook.Broadcast(BookType);
}

void UMageUIComponent::ChangeCombatMode(bool bIsCombat)
{
	OnChangeMode.Broadcast(bIsCombat);
}