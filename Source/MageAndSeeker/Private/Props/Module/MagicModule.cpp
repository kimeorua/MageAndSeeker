// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/Module/MagicModule.h"

#include "DebugHelper.h"

UMagicModule::UMagicModule()
{
	ModuleID = "Magic Module";
	UpgradeLevel = 1;
	ApplyPhase = EApplyPhase::OnMake;
	ModuleName = " ";
}

void UMagicModule::Initialize(FName InID, EApplyPhase InPhase, FName InName, int32 InLevel)
{
	ModuleID = InID;
	UpgradeLevel = InLevel;
	ApplyPhase = InPhase;
	ModuleName = InName;
	
	FString Str = "Module Crate : " + ModuleName.ToString();
	DebugHelper::Print(Str);
}