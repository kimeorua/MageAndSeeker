// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MageAndSeekerGameModeBase.h"

#include "DebugHelper.h"

AMageAndSeekerGameModeBase::AMageAndSeekerGameModeBase()
{
	DebugHelper::Print("Init GameMode");

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
