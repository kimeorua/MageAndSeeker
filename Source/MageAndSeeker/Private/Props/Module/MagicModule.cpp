#include "Props/Module/MagicModule.h"

UMagicModule::UMagicModule()
{
	ModuleID = "Magic Module";
	UpgradeLevel = 1;
	ApplyPhase = EApplyPhase::OnMake;
}

void UMagicModule::Initialize(FName InID, EApplyPhase InPhase, int32 InLevel)
{
	ModuleID = InID;
	UpgradeLevel = InLevel;
	ApplyPhase = InPhase;
}

void UMagicModule::ModuleActivate(FMagicOrbSpawnData& Data)
{
	FMagicOrbSpawnData ChangedData = ActivateModule(Data);

	if (ChangedData.OrbCount != Data.OrbCount)
	{
		Data.OrbCount = ChangedData.OrbCount;
	}
	if (ChangedData.OrbScale != Data.OrbScale)
	{
		Data.OrbScale = ChangedData.OrbScale;
	}
	if (ChangedData.Speed != Data.Speed)
	{
		Data.Speed = ChangedData.Speed;
	}
}
