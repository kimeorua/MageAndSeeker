// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/PawnUIInterface.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UMageUIComponent* IPawnUIInterface::GetMageUIComponent() const
{
	return nullptr;
}

UMonsterUIComponent* IPawnUIInterface::GetMonsterUIComponent() const
{
	return nullptr;
}