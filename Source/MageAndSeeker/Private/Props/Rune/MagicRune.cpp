// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Rune/MagicRune.h"

void UMagicRune::RuneInit(FRuneData Data)
{
	RuneData.RuneID = Data.RuneID;
	RuneData.RuneLevel = Data.RuneLevel;
	RuneData.RuneApplyType = Data.RuneApplyType;
}