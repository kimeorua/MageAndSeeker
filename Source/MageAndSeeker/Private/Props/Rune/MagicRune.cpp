// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Rune/MagicRune.h"

void UMagicRune::RuneInit(FRuneData Data)
{
	RuneData.RuneID = Data.RuneID;
	RuneData.RuneLevel = Data.RuneLevel;
	RuneData.RuneApplyType = Data.RuneApplyType;
}

FProjectileSpec UMagicRune::RuneEffect_Implementation(const FProjectileSpec& Spec)
{
	UE_LOG(LogTemp, Warning, TEXT("C++ RuneEffect called"));
	return Spec;
}