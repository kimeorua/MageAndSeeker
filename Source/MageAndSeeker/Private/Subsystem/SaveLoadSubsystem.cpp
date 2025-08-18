#include "Subsystem/SaveLoadSubsystem.h"
#include "DebugHelper.h"

void USaveLoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DebugHelper::Print("USaveLoadSubsystem Init");
}

void USaveLoadSubsystem::Deinitialize()
{
}