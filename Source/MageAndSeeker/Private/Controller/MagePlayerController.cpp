// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MagePlayerController.h"

AMagePlayerController::AMagePlayerController()
{
	MageTeamId = FGenericTeamId(0);
}

FGenericTeamId AMagePlayerController::GetGenericTeamId() const
{
	return MageTeamId;
}